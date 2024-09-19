#include "pacman.hpp"
#include "Game.hpp"
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_timer.h>

Game::Game(const char *map_path): _window(nullptr), _renderer(nullptr), _w_height(0), _w_width(0) {
	_load_map(map_path);
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0
	|| !(_window = SDL_CreateWindow("Pacman", 0, 0, _w_width, _w_height, SDL_WINDOW_SHOWN))
	|| !(_renderer = SDL_CreateRenderer(_window, 0, 0))) {
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	_draw_map(true);
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

void Game::_draw_map(bool init) {
	SDL_Rect rect;

	rect.x = 0;
	rect.y = 0;
	rect.w = TILE_SIZE;
	rect.h = TILE_SIZE;
	for(std::vector<std::string>::iterator m_it = _map.begin(); m_it != _map.end(); m_it++) {
		for (std::string::iterator c_it =m_it->begin(); c_it != m_it->end(); c_it++) {
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
					if (init) {
						_player.x = rect.x;
						_player.y = rect.y;
					}
					*c_it = Entity::Empty;
					break;
				case Entity::Ghost:
					SDL_SetRenderDrawColor(_renderer, (Colors::Ghost >> 16) & 0xff, (Colors::Ghost >> 8) & 0xff, Colors::Ghost & 0xff, 255);
					break;
				default:
					SDL_SetRenderDrawColor(_renderer, (Colors::Empty >> 16) & 0xff, (Colors::Empty >> 8) & 0xff, Colors::Empty & 0xff, 255);
					break;
			}
			SDL_RenderDrawRect(_renderer, &rect);
			SDL_RenderFillRect(_renderer, &rect);
			rect.x += TILE_SIZE;
		}
		rect.x = 0;
		rect.y += TILE_SIZE;
	}
	// draw player
	rect.x = _player.x;
	rect.y = _player.y;
	SDL_SetRenderDrawColor(_renderer, (Colors::Pacman >> 16) & 0xff, (Colors::Pacman >> 8) & 0xff, Colors::Pacman & 0xff, 255);
	SDL_RenderDrawRect(_renderer, &rect);
	SDL_RenderFillRect(_renderer, &rect);
	// Need to draw ghosts

	SDL_RenderPresent(_renderer);
}

void Game::_update_player_map_pos(void) {
	_map[_player.y / TILE_SIZE][_player.x / TILE_SIZE] = Entity::Pacman;
}

void Game::loop(void) {
	int		frame_time;
	bool		run;
	Uint32		frame_start;
	const int	frame_delay = 1000 / FPS;

	run = true;
	frame_time = 0;
	frame_start = 0;
	while (run) {
		frame_start = SDL_GetTicks();
		_update_player_map_pos();
		_draw_map(false);
		while (SDL_PollEvent(&_ev)) {
			switch (_ev.type) {
				case SDL_QUIT:
					run = false;
					break;
				case SDL_KEYDOWN:
					// Need to make pacman move alone
					// The player only changes the direction
					// where pacman goes
					_handle_key();
					break;
				default:
					break;
			}
		}
		if (run) {
			frame_time = SDL_GetTicks() - frame_start;
			if (frame_delay > frame_time)
				SDL_Delay(frame_delay - frame_time);
		}
	}
}

void Game::_handle_key(void) {
	int new_pos;

	new_pos = 0;
	// In the future I will need to check for ghost position and state
	switch (_ev.key.keysym.sym) {
		// don't like this switch statement: too repetitive
		case SDLK_UP:
			new_pos = _player.y - TILE_SIZE;
			if (new_pos >= 0
				&& _map[new_pos / TILE_SIZE][_player.x / TILE_SIZE] != Entity::Wall)
				_player.y = new_pos;
			break;
		case SDLK_DOWN:
			new_pos = _player.y + TILE_SIZE;
			if (static_cast<size_t>(new_pos) < _w_height
				&& _map[new_pos / TILE_SIZE][_player.x / TILE_SIZE] != Entity::Wall)
				_player.y = new_pos;
			break;
		case SDLK_LEFT:
			new_pos = _player.x - TILE_SIZE;
			if (new_pos >= 0
				&& _map[_player.y / TILE_SIZE][new_pos / TILE_SIZE] != Entity::Wall)
				_player.x = new_pos;
			break;
		case SDLK_RIGHT:
			new_pos = _player.x + TILE_SIZE;
			if (static_cast<size_t>(new_pos) < _w_width
				&& _map[_player.y / TILE_SIZE][new_pos / TILE_SIZE] != Entity::Wall)
				_player.x = new_pos;
			break;
		default:
			break;
	}
}
