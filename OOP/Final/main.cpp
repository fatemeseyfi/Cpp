/*
#include <SDL.h>
#include <string>
#include <tuple>
#include "Constants.h"



int main(int argc, char* argv[]) {



	const int WINDOW_SIZE = 640;
	const int MARGIN = 20;
	const int LINE_WIDTH = 5;
	const int CELL_COUNT = 9;
	const int CELL_SIZE = (WINDOW_SIZE - 2 * MARGIN) / CELL_COUNT;

	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_CreateWindowAndRenderer(WINDOW_SIZE, WINDOW_SIZE, 0, &window, &renderer);

	

	SDL_Event event;


	while (true) {

		//-- event handeling --------------------------------------------------

		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
			break;
		}

		COLOR(230, 90, 10);
		// clear renderer
		SDL_RenderClear(renderer);


		
		// set draw on renderer
		SDL_RenderPresent(renderer);

	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();


	//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "HELLO WORLD", "Successful", NULL);
	return 0;

}*/


#include <SDL.h>
#include "Rectangle.h"
#include "Triangle.h"
#include "Size.h"
#include "Square.h"
#include "Elipse.h"
#include "Polygon.h"
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "ShapeFactory.h"
#include <iostream>



int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Rotated Ellipse", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	std::vector<Point> pts = {
		Point(20,40),
		Point(50,80),
		Point(60,40),
	};
	Triangle t(pts);
	

	Point center(90, 90);
	Size size(30, 50);
	float a = 0;
	IShape::ShapeType type = (IShape::ShapeType)0;
	//IShape* r = ShapeFactory::create(type, size, center, a);

	bool running = true;
	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		ShapeFactory::DrawShapes(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
