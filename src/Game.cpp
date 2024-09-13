#include "Game.hpp"

Game::Game(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0
	|| !(_window = SDL_CreateWindow("Pacman", 0, 0, 1920, 1080, SDL_WINDOW_SHOWN))) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}
}

Game::~Game(void) {
	if (_window)
		free(_window);
}