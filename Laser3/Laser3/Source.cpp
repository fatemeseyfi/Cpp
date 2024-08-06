#include <iostream>
#include <SDL.h>
#include <string>


// -- a struct to keep the values of coordinate -- 
struct coor {
	double x;
	double y;
};

// -- global variables to use them in the recursive function -- 
// dimensions:
int n = 1;
int m = 1;


// -- graphic ------------------------------------------------------------

int WINDOW_SIZE = 600;
int MARGIN = 20;
double CELL_SIZEX;
double CELL_SIZEY;


void showBoard(SDL_Renderer* renderer, int n, int m) {
	double CELL_SIZEX = (WINDOW_SIZE - 2 * MARGIN) / m;
	double CELL_SIZEY = (WINDOW_SIZE - 2 * MARGIN) / n;
	int x1, x2, y1, y2;

	// -- draw vertical lines --------------------------
	for (int i = 0; i <= m; i++) {
		x1 = i * CELL_SIZEX + MARGIN;
		x2 = MARGIN;
		y1 = i * CELL_SIZEX + MARGIN;
		y2 = WINDOW_SIZE - MARGIN;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
		SDL_RenderDrawLine(renderer, x1, x2, y1, y2);

	}

	// -- draw horizontal lines --------------------------

	for (int i = 0; i <= n; i++) {
		x1 = MARGIN;
		x2 = i * CELL_SIZEY + MARGIN;
		y1 = WINDOW_SIZE - MARGIN;
		y2 = i * CELL_SIZEY + MARGIN;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
		SDL_RenderDrawLine(renderer, x1, x2, y1, y2);

	}

}

void drawLaser(SDL_Renderer* renderer, coor src, coor dest) {

	CELL_SIZEX = (WINDOW_SIZE - 2 * MARGIN) / m;
	CELL_SIZEY = (WINDOW_SIZE - 2 * MARGIN) / n;

	double centerSrcX = MARGIN + (src.x + 0.5) * CELL_SIZEX;
	double centerSrcY = MARGIN + (src.y + 0.5) * CELL_SIZEY;
	double centerDestX = MARGIN + (dest.x + 0.5) * CELL_SIZEX;
	double centerDestY = MARGIN + (dest.y + 0.5) * CELL_SIZEY;

	SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); 
	SDL_RenderDrawLine(renderer, centerSrcX, centerSrcY, centerDestX, centerDestY);
	SDL_RenderDrawLine(renderer, centerSrcX, centerSrcY, centerDestX, centerDestY);
	SDL_RenderPresent(renderer);

}

// -- laser --------------------------------------------------------------

// -- the recursive function. it gets the current coordinate and a direction and it reflects the laser r times recursively -- 
coor laser(SDL_Renderer* renderer, coor currentCoor, std::string direct, int r) {

	// -- it was reflected r times so it stops --
	if (r == 0) {
		return currentCoor;
	}

	int newX = 0;
	int newY = 0;
	coor pre_coor = { currentCoor.x, currentCoor.y };

	// -- checks 4 possible directions and generates new coordinate and possible directions for it --
	if (direct == "top_right") {
		// catch exceptions: it won't let laser move anymore
		if ((currentCoor.x == m - 1) ||
			(currentCoor.y == n - 1))  return currentCoor;

		if (n - 1 - currentCoor.y < m - 1 - currentCoor.x) {
			newX = currentCoor.x + (n - 1 - currentCoor.y);
			newY = n - 1;
			currentCoor.x = newX;
			currentCoor.y = newY;
			direct = "bottom_right";
			r = r - 1;
		}
		else if (n - currentCoor.y > m - currentCoor.x) {
			newX = m - 1;
			newY = currentCoor.y + (m - 1 - currentCoor.x);
			currentCoor.x = newX;
			currentCoor.y = newY;
			direct = "top_left";
			r = r - 1;
		}
		else {
			newX = m - 1;
			newY = n - 1;
			currentCoor.x = newX;
			currentCoor.y = newY;
			direct = "bottom_left";
			r = r - 1;
		}

	}

	else if (direct == "top_left") {
		// catch exceptions: it won't let laser move anymore
		if ((currentCoor.x == 0) ||
			(currentCoor.y == n - 1))  return currentCoor;

		if (n - 1 - currentCoor.y < currentCoor.x) {
			newX = currentCoor.x - (n - 1 - currentCoor.y);
			newY = n - 1;
			currentCoor.x = newX;
			currentCoor.y = newY;
			direct = "bottom_left";
			r = r - 1;
		}
		else if (n - currentCoor.y > currentCoor.x) {
			newX = 0;
			newY = currentCoor.y + currentCoor.x;
			currentCoor.x = newX;
			currentCoor.y = newY;
			direct = "top_right";
			r = r - 1;
		}
		else {
			newX = 0;
			newY = n - 1;
			currentCoor.x = newX;
			currentCoor.y = newY;
			direct = "bottom_right";
			r = r - 1;
		}

	}

	else if (direct == "bottom_right") {
		// catch exceptions: it won't let laser move anymore
		if ((currentCoor.x == m - 1) ||
			(currentCoor.y == 0))  return currentCoor;

		if (currentCoor.y > m - 1 - currentCoor.x) {
			newX = m - 1;
			newY = currentCoor.y - (m - 1 - currentCoor.x);
			currentCoor.x = newX;
			currentCoor.y = newY;
			direct = "bottom_left";
			r = r - 1;
		}
		else if (currentCoor.y < m - 1 - currentCoor.x) {
			newX = currentCoor.x + currentCoor.y;
			newY = 0;
			currentCoor.x = newX;
			currentCoor.y = newY;
			direct = "top_right";
			r = r - 1;
		}
		else {
			newX = m - 1;
			newY = 0;
			currentCoor.x = newX;
			currentCoor.y = newY;
			direct = "bottom_right";
			r = r - 1;
			
		}
	}

	else if (direct == "bottom_left") {
		// catch exceptions: it won't let laser move anymore
		if ((currentCoor.x == 0) ||
			(currentCoor.y == 0))  return currentCoor;

		if (currentCoor.y < currentCoor.x) {
			newX = currentCoor.x - currentCoor.y;
			newY = 0;
			currentCoor.x = newX;
			currentCoor.y = newY;
			direct = "top_left";
			r = r - 1;
		}
		else if (currentCoor.y > currentCoor.x) {
			newX = 0;
			newY = currentCoor.y - currentCoor.x;
			currentCoor.x = newX;
			currentCoor.y = newY;
			direct = "bottom_right";
			r = r - 1;
		}
		else {
			newX = 0;
			newY = 0;
			currentCoor.x = newX;
			currentCoor.y = newY;
			direct = "top_right";
			r = r - 1;
		}
	}

	// -- returns the destination coordinate with new current coordinate and new direction -- 
	// -- draws the new laser -- 
	drawLaser(renderer, pre_coor, currentCoor);
	return laser(renderer, currentCoor, direct, r);
}

int main(int argc, char* argv[]) {


	// -- gets inputs -- 

	// dimensions: 
	std::cout << "Enter m: ";
	std::cin >> m;

	std::cout << "Enter n: ";
	std::cin >> n;


	// r:
	int r = -1;
	while (r < 0 || r >100) {
		std::cout << "Enter r (0,100): ";
		std::cin >> r;
	}

		// src coordinate: 
	coor src;
	src.x = -1;
	src.y = -1;

	while (src.x < 0 || src.x >m - 1 || src.y < 0 || src.y > n - 1) {
		std::cout << "Enter src x: ";
		std::cin >> src.x;

		std::cout << "Enter src y: ";
		std::cin >> src.y;
	}

	// direction:
	std::string direct = "";

	std::cout << "Enter direct in this format: top_right * top_left * bottom_right * bottom_left \n" ;
	std::cout << "Be careful about underline between directions \n";
	while (direct != "top_right" && direct != "top_left" && direct != "bottom_right" && direct != "bottom_left") {
		std::cout << "Enter direct: ";
		std::cin >> direct;
	}

	// ---------------------------------------------------------------------------------------------------------------------

	// -- graphic part --
		
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		SDL_Event event;
		SDL_CreateWindowAndRenderer(WINDOW_SIZE, WINDOW_SIZE, 0, &window, &renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to white
		SDL_RenderClear(renderer);

	// ---------------------------------------------------------------------------------------------------------------------

		
		showBoard(renderer, n, m);
		
		// -- laser function --
		coor dest = laser(renderer, src, direct, r);

		// -- dest coordinate --
		std::cout << "dest x : ";
		std::cout << dest.x << "\n";
		std::cout << "dest y : ";
		std::cout << dest.y;


		// -- set the src coordinate as green and dest coordinate as red --
		double centerSrcX = MARGIN + (src.x + 0.5) * CELL_SIZEX;
		double centerSrcY = MARGIN + (src.y + 0.5) * CELL_SIZEY;
		double centerDestX = MARGIN + (dest.x + 0.5) * CELL_SIZEX;
		double centerDestY = MARGIN + (dest.y + 0.5) * CELL_SIZEY;

		int size = 10; // Size of the square

		SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); // Set color to white
		SDL_Rect pointRectS = { centerSrcX - size / 2, centerSrcY - size / 2, size, size }; // Center the square around the point
		SDL_RenderFillRect(renderer, &pointRectS);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set color to white
		SDL_Rect pointRectD = { centerDestX - size / 2, centerDestY - size / 2, size, size }; // Center the square around the point
		SDL_RenderFillRect(renderer, &pointRectD);
		SDL_RenderPresent(renderer);






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