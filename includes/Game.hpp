#pragma once
#include "pacman.hpp"

using namespace std;

class Game {
	public:
		Game();
		~Game();
	
		void loop(void);
	
	private:
		SDL_Window *_window;
		SDL_Surface *_surface;
		SDL_Event _ev;
};
