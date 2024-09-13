#pragma once
#include "pacman.hpp"

using namespace std;

class Game {
	public:
		Game();
		~Game();
	
	private:
		SDL_Window *_window;
};