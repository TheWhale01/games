#include "Game.hpp"
#include "pacman.hpp"
#include <SDL_render.h>
#include <vector>

Game::Game(const char *map_path): _window(nullptr), _renderer(nullptr), _w_height(0), _w_width(0) {
	_load_map(map_path);
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0
	|| !(_window = SDL_CreateWindow("Pacman", 0, 0, _w_width, _w_height, SDL_WINDOW_SHOWN))
	|| !(_renderer = SDL_CreateRenderer(_window, 0, 0))) {
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	_draw_map();
}

Game::~Game(void) {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	_window = nullptr;
	_renderer = nullptr;
	SDL_Quit();
}

void Game::_load_map(const char *map_path) {
	std::ifstream mapfile;
	std::string line;

	mapfile.open(map_path);
	while (getline(mapfile, line)) {
		_map.push_back(line);
		_w_height++;
	}
	mapfile.close();
	if (_map.empty()) {
		std::cerr << "Map is empty" << std::endl;
		exit(EXIT_FAILURE);
	}
	_w_width = _map[0].size() * TILE_SIZE;
	_w_height *= TILE_SIZE;
}

void Game::_draw_map(void) {
	SDL_Rect rect;

	rect.x = 0;
	rect.y = 0;
	rect.w = TILE_SIZE;
	rect.h = TILE_SIZE;
	for(std::vector<std::string>::const_iterator m_it = _map.cbegin(); m_it != _map.cend(); m_it++) {
		for (std::string::const_iterator c_it =m_it->cbegin(); c_it != m_it->cend(); c_it++) {
			switch (*c_it) {
				case Entity::Wall:
					SDL_SetRenderDrawColor(_renderer, (Colors::Wall >> 16) & 0xff, (Colors::Wall >> 8) & 0xff, Colors::Wall & 0xff, 255);
					break;
				case Entity::Fruit:
					SDL_SetRenderDrawColor(_renderer, (Colors::Fruit >> 16) & 0xff, (Colors::Fruit >> 8) & 0xff, Colors::Fruit & 0xff, 255);
					break;
				case Entity::Dot:
					SDL_SetRenderDrawColor(_renderer, (Colors::Dot >> 16) & 0xff, (Colors::Dot >> 8) & 0xff, Colors::Dot & 0xff, 255);
					break;
				case Entity::Pacman:
					SDL_SetRenderDrawColor(_renderer, (Colors::Pacman >> 16) & 0xff, (Colors::Pacman >> 8) & 0xff, Colors::Pacman & 0xff, 255);
					break;
				case Entity::Ghost:
					SDL_SetRenderDrawColor(_renderer, (Colors::Ghost >> 16) & 0xff, (Colors::Ghost >> 8) & 0xff, Colors::Ghost & 0xff, 255);
					break;
				case Entity::Empty:
					SDL_SetRenderDrawColor(_renderer, (Colors::Empty >> 16) & 0xff, (Colors::Empty >> 8) & 0xff, Colors::Empty & 0xff, 255);
					break;
				default:
					break;
			}
			SDL_RenderDrawRect(_renderer, &rect);
			SDL_RenderFillRect(_renderer, &rect);
			rect.x += TILE_SIZE;
		}
		rect.x = 0;
		rect.y += TILE_SIZE;
	}
	SDL_RenderPresent(_renderer);
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
