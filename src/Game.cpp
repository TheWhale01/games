#include "Game.hpp"
#include <SDL_events.h>
#include <SDL_video.h>

Game::Game(void): _window(nullptr), _surface(nullptr) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0
	|| !(_window = SDL_CreateWindow("Pacman", 0, 0, 1920, 1080, SDL_WINDOW_SHOWN))
	|| !(_surface = SDL_GetWindowSurface(_window))) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}
}

Game::~Game(void) {
	SDL_DestroyWindow(_window);
	_window = nullptr;
	_surface = nullptr;
	SDL_Quit();
}

void Game::loop(void) {
	int run = true;
	while (run) {
		while (SDL_PollEvent(&_ev)) {
			switch (_ev.type) {
				case SDL_QUIT:
					run = false;
					break;
				default:
					break;
			}
		}
	}
}
