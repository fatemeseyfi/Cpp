#include <SDL.h>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define COLOR(r,g,b) SDL_SetRenderDrawColor(renderer, r, g, b, 0);
struct Point {
	double x;
	double y;
};

struct Line {
	double x1;  // src.getX()
	double y1;  // src.getY()
	double x2;  // dst.getX()
	double y2;  // dst.getY()
	
};


// -- variables ----------------------------------------------------------


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int MARGIN = 20;
int SIZE = 4;
int crossedSIZE = 0;

std::vector<Point> seen;


// -- graphic -------------------------------------------------------------


void drawCities(SDL_Renderer* renderer,Point* cities[]) {

	
	int size = 10; // Size of the square

	int x = (*cities[0]).x;
	int y = (*cities[0]).y;
	COLOR(255, 0, 0); // Set color to red
	SDL_Rect pointRect = { x - size / 2, y - size / 2, size, size }; // Center the square around the point
	SDL_RenderFillRect(renderer, &pointRect);

	for (int i = 1; i < SIZE; i++) { 
		x = (*cities[i]).x;
		y = (*cities[i]).y;
		COLOR(255, 255, 255); // Set color to white
		SDL_Rect pointRect = { x - size / 2, y - size / 2, size, size }; // Center the square around the point
		SDL_RenderFillRect(renderer, &pointRect);
	}


}

void drawPath(SDL_Renderer* renderer,Line line) {
	COLOR(255, 255, 255);
	SDL_RenderDrawLine(renderer, line.x1, line.y1, line.x2, line.y2);
}

void drawWalk(SDL_Renderer* renderer, std::vector<Line*> crossed, Point* cities[]) {

	//-- event handeling --------------------------------------------------

	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
		exit(0);
	}

	//----------------------------------------------------------------------

	// clear renderer
	COLOR(34, 139, 34);
	SDL_RenderClear(renderer);


	// --- draw path -----------------------------------------------------

	drawCities(renderer, cities);

	for (int i = 0; i < crossed.size(); i++) {
		drawPath(renderer, (*crossed[i]));
	}

	SDL_RenderPresent(renderer);
	SDL_Delay(100);
}



// -- Salesman ------------------------------------------------------------

Point** coordinates() {

	Point** cities = new Point* [SIZE];


	for (int i = 0; i < SIZE; i++) {

		cities[i] = new Point; // Allocate memory for each Point object


		std::cout << "---------coordinates of city " << i + 1 << "----------\n";

		int x;
		std::cout << "Enter a value for x (0, 600): ";
		std::cin >> x;
		while (x < 0 || x > 600) {
			std::cout << "Enter a value for x (0, 600): ";
			std::cin >> x;
		}
		cities[i]->x = x;

		int y;
		std::cout << "Enter a value for y (0, 600): ";
		std::cin >> y;
		while (y < 0 || y > 600) {
			std::cout << "Enter a value for y (0, 600): ";
			std::cin >> y;
		}
		cities[i]->y = y;

		std::cout << "\n";



	}
	return cities;

}

bool HasSeen(std::vector<Point> seen, Point city){
	bool has = false;

	for (int i = 0; i < seen.size(); i++) {
		if (seen[i].x == city.x && seen[i].y == city.y) {
			has = true;
			break;
		}
	}
	
	return has;
	

	
}

bool validate(std::vector<Line*> crossed, Line newLine) {

	bool ok = true;


	double new_m, new_c, m, c;
	double x_intersect = 0;
	double y_intersect = 0;
	double new_XDelta, new_YDelta, XDelta, YDelta;

	for (int i = 0; i < crossed.size(); i++) {

		new_XDelta = newLine.x2 - newLine.x1;
		new_YDelta = newLine.y2 - newLine.y1;
		XDelta = (*crossed[i]).x2 - (*crossed[i]).x1;
		YDelta = (*crossed[i]).y2 - (*crossed[i]).y1;

		if ((newLine.x1 == (*crossed[i]).x1 && newLine.y1 == (*crossed[i]).y1) ||
			(newLine.x1 == (*crossed[i]).x2 && newLine.y1 == (*crossed[i]).y2) ||
			(newLine.x2 == (*crossed[i]).x1 && newLine.y2 == (*crossed[i]).y1) ||
			(newLine.x2 == (*crossed[i]).x2 && newLine.y2 == (*crossed[i]).y2))
			continue;


		if (new_XDelta != 0 && XDelta != 0) {
			if (new_YDelta != 0 && YDelta != 0) {
				new_m = new_YDelta / new_XDelta;
				new_c = newLine.y1 - (new_m * newLine.x1);
				m = YDelta / XDelta;
				c = (*crossed[i]).y1 - (m * (*crossed[i]).x1);
				x_intersect = -(new_c - c) / (new_m - m);
				y_intersect = new_m * x_intersect + new_c;

			}
			else if (new_YDelta == 0 && YDelta != 0) {
				m = YDelta / XDelta;
				c = (*crossed[i]).y1 - (m * (*crossed[i]).x1);

				x_intersect = (newLine.y1 - c) / m;
				y_intersect = newLine.y1;
			}
			else if (new_YDelta != 0 && YDelta == 0) {
				new_m = new_YDelta / new_XDelta;
				new_c = newLine.y1 - (new_m * newLine.x1);
				x_intersect = ((*crossed[i]).y1 - new_c) / new_m;
				y_intersect = (*crossed[i]).y1;
			}
			else {


				if ((newLine.x1 > std::min((*crossed[i]).x2, (*crossed[i]).x1) && newLine.x1 < std::max((*crossed[i]).x2, (*crossed[i]).x1)) ||
					(newLine.x2 > std::min((*crossed[i]).x2, (*crossed[i]).x1) && newLine.x2 < std::max((*crossed[i]).x2, (*crossed[i]).x1))) {
					ok = false;

				}
			}
		}
		else if (new_XDelta == 0 && XDelta != 0) {

			m = YDelta / XDelta;
			c = (*crossed[i]).y1 - (m * (*crossed[i]).x1);

			x_intersect = newLine.x1;
			y_intersect = m * x_intersect + c;

		}
		else if (new_XDelta == 0 && XDelta == 0) {

			if ((newLine.y1 > std::min((*crossed[i]).y2, (*crossed[i]).y1) && newLine.y1 < std::max((*crossed[i]).y2, (*crossed[i]).y1)) ||
				(newLine.y2 > std::min((*crossed[i]).y2, (*crossed[i]).y1) && newLine.y2 < std::max((*crossed[i]).y2, (*crossed[i]).y1))) {
				ok = false;
				break;
			}

		}
		else if (new_XDelta != 0 && XDelta == 0) {

			new_m = new_YDelta / new_XDelta;
			new_c = newLine.y1 - (new_m * newLine.x1);

			x_intersect = (*crossed[i]).x1;
			y_intersect = new_m * x_intersect + new_c;

		}


		// Check if the intersection point lies within the range of the existing line segment
		if (ok) {
			if (x_intersect >= std::min((*crossed[i]).x2, (*crossed[i]).x1) && x_intersect <= std::max((*crossed[i]).x2, (*crossed[i]).x1) &&
				y_intersect >= std::min((*crossed[i]).y2, (*crossed[i]).y1) && y_intersect <= std::max((*crossed[i]).y2, (*crossed[i]).y1) &&
				x_intersect >= std::min(newLine.x2, newLine.x1) && x_intersect <= std::max(newLine.x2, newLine.x1) &&
				y_intersect >= std::min(newLine.y2, newLine.y1) && y_intersect <= std::max(newLine.y2, newLine.y1)) {
				ok = false;
				break;
			}
		}

	}

	return ok;


}

/*bool validate(const std::vector<Line*>& crossed, const Line& newLine) {
	for (const auto& line : crossed) {
		const double XDelta = line->x2 - line->x1;
		const double YDelta = line->y2 - line->y1;

		// Check if any endpoint of newLine coincides with any endpoint of crossed[i]
		if ((newLine.x1 == line->x1 && newLine.y1 == line->y1) ||
			(newLine.x1 == line->x2 && newLine.y1 == line->y2) ||
			(newLine.x2 == line->x1 && newLine.y2 == line->y1) ||
			(newLine.x2 == line->x2 && newLine.y2 == line->y2)) {
			continue;
		}

		// Check if lines are parallel or coincident
		if (XDelta == 0 && newLine.x1 == line->x1) {
			// Lines are vertical and coincident
			if ((newLine.y1 >= std::min(line->y1, line->y2) && newLine.y1 <= std::max(line->y1, line->y2)) ||
				(newLine.y2 >= std::min(line->y1, line->y2) && newLine.y2 <= std::max(line->y1, line->y2))) {
				return false;
			}
		}
		else if (newLine.x1 == newLine.x2) {
			// New line is vertical
			if ((line->x1 >= std::min(newLine.x1, newLine.x2) && line->x1 <= std::max(newLine.x1, newLine.x2)) &&
				(line->y1 >= std::min(newLine.y1, newLine.y2) && line->y1 <= std::max(newLine.y1, newLine.y2))) {
				return false;
			}
		}
		else {
			// Lines are not vertical or coincident
			const double new_m = (newLine.y2 - newLine.y1) / (newLine.x2 - newLine.x1);
			const double new_c = newLine.y1 - (new_m * newLine.x1);
			const double m = YDelta / XDelta;
			const double c = line->y1 - (m * line->x1);

			// Calculate intersection point
			const double x_intersect = (new_c - c) / (m - new_m);
			const double y_intersect = new_m * x_intersect + new_c;

			// Check if the intersection point lies within the range of both lines
			if ((x_intersect >= std::min(line->x1, line->x2) && x_intersect <= std::max(line->x1, line->x2)) &&
				(y_intersect >= std::min(line->y1, line->y2) && y_intersect <= std::max(line->y1, line->y2)) &&
				(x_intersect >= std::min(newLine.x1, newLine.x2) && x_intersect <= std::max(newLine.x1, newLine.x2)) &&
				(y_intersect >= std::min(newLine.y1, newLine.y2) && y_intersect <= std::max(newLine.y1, newLine.y2))) {
				return false;
			}
		}
	}
	return true;
}
*/
bool Salesman(SDL_Renderer* renderer, std::vector<Line*>& crossed, Point* cities[], Point srcCity, Point currentCity) {

	//first condition 
	if (seen.size() == SIZE) {
		Line newLine = { currentCity.x, currentCity.y, srcCity.x, srcCity.y };

		if (validate(crossed, newLine)) {
			crossed.push_back(&newLine);
			drawWalk(renderer, crossed, cities);
		    return true;
		}
	}



	for (int i = 0; i < SIZE; i++) {

		Point p = { (*cities[i]).x, (*cities[i]).y };

		if ((currentCity.x == (*cities[i]).x && currentCity.y == (*cities[i]).y) || HasSeen(seen, p)) continue;
		
		Line newLine = { currentCity.x, currentCity.y, (*cities[i]).x, (*cities[i]).y };

		if (crossed.empty()) {
			crossed.push_back(&newLine);
			seen.push_back(p);
			drawWalk(renderer, crossed, cities);
			if (Salesman(renderer, crossed, cities, srcCity, p)) return true;
			
		}
		else if (validate(crossed, newLine)) {
			crossed.push_back(&newLine);
			seen.push_back(p);
			drawWalk(renderer, crossed,cities);
			if (Salesman(renderer, crossed, cities, srcCity, p)) return true;
		}
			}
	if (!crossed.empty()) {
		crossed.pop_back();
	}
	if (!seen.empty()){
		seen.pop_back();
}
	return false;


}

/*std::vector<Line*> createCrossedArr() {


	std::vector<Line*> crossed(SIZE);

	for (int i = 0; i < SIZE; i++) {
		crossed[i] = new Line;
		(*crossed[i]).x1 = 0;
		(*crossed[i]).y1 = 0;
		(*crossed[i]).x2 = 0;
		(*crossed[i]).y2 = 0;
	}

	return crossed;


	
}*/

void destroyCrossedArr(Line** crossed) {

	for (int i = 0; i < SIZE; i++) {
		delete crossed[i];
	}
	delete crossed;
	
}


int main(int argc, char* argv[]) {

	// -- get N input from user ----------------------------------------------


	std::cout << "Enter number of cities: ";
	std::cin >> SIZE;

	Point** cities = coordinates();
	std::vector<Line*> crossed;

	Point src = { cities[0]->x, cities[0]->y };
	seen.push_back(src);

	// -- initial SDL --------------------------------------------------------------------
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

	// -- Salesman -----------------------------------------------------------

	
	drawWalk(renderer, crossed, cities);
	Salesman(renderer, crossed, cities, src, src);

	
	while (true) {

		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
			exit(0);
		}
		
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	
	return 0;
}
