#include <iostream>
#include <vector>
#include <cmath>
#include <SDL.h>
#define COLOR(r,g,b) SDL_SetRenderDrawColor(renderer, r, g, b, 0);
void drawQueens(SDL_Renderer* renderer, std::vector<int>& board);
void drawBoard(SDL_Renderer* renderer, std::vector<int>& board);

// -- variables ---------------------------------------------
const int WINDOW_SIZE = 640;
const int MARGIN = 20;
int CELL_COUNT;
int CELL_SIZE;


// -- N Queen -----------------------------------------------

bool validate(std::vector<int>& board, int r, int c) {

	bool ok = true;

	// -- check rows ------------------
	for (int i = 0; i < board.size(); i++) {
		if (board[i] == r) {
			ok = false;
			break;
		}
	}

	// -- check Diameter ------------------
	for (int i = 0; i < board.size(); i++) {
		if (abs(c - i) == abs(r - board[i])) 
			ok = false;
		
		if (board[i] == 0) 
			break;
		
	}
	return ok;
}

bool N_Queen(SDL_Renderer* renderer,std::vector<int>& board, int c) {

	if (c == board.size()) 
		return true;
	

	for (int i = 1; i <= board.size(); i++) {
		if (!validate(board, i, c)) 
			continue;

		board[c] = i;
		drawBoard(renderer, board);
		if (N_Queen(renderer, board, c + 1)) 
			return true;
		

	}
	board[c] = 0;
	//drawQueens(renderer, board);
	return false;

}

// -- show ------------------------------------------------------
void printBoard(std::vector<int>& board) {

	for (int c = 0; c < board.size(); c++) {
		std::cout << board[c] << " ";

	}
	std::cout << "\n";
	std::cout << "\n";

	
	for (int c = 0; c < board.size(); c++) {
		for (int r = 0; r < board.size(); r++) {
			if (board[c]-1 == r)
				std::cout << "1" << " ";
			else
				std::cout << "0" << " ";
		}
		std::cout << "\n";
	}
}

void drawLines(SDL_Renderer* renderer,int CELL_COUNT, int CELL_SIZE, int MARGIN, int WINDOW_SIZE) {

	int x1,x2,y1, y2;

	// -- draw vertical lines --------------------------
	for (int i = 0; i <= CELL_COUNT; i++) {
		x1 = i * CELL_SIZE + MARGIN;
		x2 = MARGIN;
		y1 = i * CELL_SIZE + MARGIN;
		y2 = WINDOW_SIZE - MARGIN;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to white
		SDL_RenderDrawLine(renderer, x1, x2, y1, y2);

	}

	// -- draw horizontal lines --------------------------

	for (int i = 0; i <= CELL_COUNT; i++) {
		x1 = MARGIN;
		x2 = i * CELL_SIZE + MARGIN;
		y1 = WINDOW_SIZE - MARGIN;
		y2 = i * CELL_SIZE + MARGIN;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to white
		SDL_RenderDrawLine(renderer, x1, x2, y1, y2);

	}
}

void drawQueens(SDL_Renderer* renderer, std::vector<int>& board) {

	auto getCenter = [&](int r, int c, int& x, int& y) {

		x = MARGIN + (c + 0.5) * CELL_SIZE;
		y = MARGIN + (r + 0.5) * CELL_SIZE;

		};

	int r = -1;
	int x, y;
	bool r0_flag = false;
	bool c0_flag = false;

	for (int c = 0; c < CELL_COUNT; c++) {

		if (r0_flag && r == 0) { 
			COLOR(180, 90, 100);
			SDL_RenderClear(renderer);
			continue; 
		}

		int r = board[c] - 1;
		if (r == 0) r0_flag = true;

		
		
		getCenter(r, c, x, y);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to white
		int size = 10; // Size of the square
		SDL_Rect pointRect = { x - size / 2, y - size / 2, size, size }; // Center the square around the point
		SDL_RenderFillRect(renderer, &pointRect);

	}
	
}

void drawBoard(SDL_Renderer* renderer, std::vector<int>& board) {
	//-- event handeling --------------------------------------------------

	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
		exit(0);
	}

	//----------------------------------------------------------------------

	// clear renderer
	COLOR(180, 90, 100);
	SDL_RenderClear(renderer);

	drawLines(renderer, CELL_COUNT, CELL_SIZE, MARGIN, WINDOW_SIZE);

	// --- draw queens -----------------------------------------------------

	auto getCenter = [&](int r, int c, int& x, int& y) {

		x = MARGIN + (c + 0.5) * CELL_SIZE;
		y = MARGIN + (r + 0.5) * CELL_SIZE;

		};

		int r = -1;
		int x, y;
		bool r0_flag = false;
		bool c0_flag = false;

		for (int c = 0; c < CELL_COUNT; c++) {

			if (r0_flag && r == 0) {
				COLOR(180, 90, 100);
				SDL_RenderClear(renderer);
				continue;
			}

			int r = board[c] - 1;
			if (r == 0) r0_flag = true;



			getCenter(r, c, x, y);

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to white
			int size = 10; // Size of the square
			SDL_Rect pointRect = { x - size / 2, y - size / 2, size, size }; // Center the square around the point
			SDL_RenderFillRect(renderer, &pointRect);
		}


	

			SDL_RenderPresent(renderer);
			SDL_Delay(60);

}



// -- main -----------------------------------------------------------
int main(int argc, char* argv[]) {

	


	// get input N 
	std::cout << "Enter number of queens: ";
	int n = 0;
	std::cin >> n;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(WINDOW_SIZE, WINDOW_SIZE, 0, &window, &renderer);


	CELL_COUNT = n;
	CELL_SIZE = (WINDOW_SIZE - 2 * MARGIN) / CELL_COUNT;


	std::vector<int> board(n);
	
	drawBoard(renderer, board);	
	N_Queen(renderer, board,0);

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