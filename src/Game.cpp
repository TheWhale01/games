#include "pacman.hpp"
#include "Game.hpp"
#include "Blinky.hpp"
#include "Inky.hpp"
#include "Clyde.hpp"
#include "Pinky.hpp"

Game::Game(const char *map_path): _window(nullptr), _renderer(nullptr), _w_height(0),
	_w_width(0), _player(nullptr) {
	_ghosts.reserve(4);
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
	for (size_t i = 0; i < _ghosts.size(); i++)
		if (_ghosts[i])
			delete _ghosts[i];
	if (_player)
		delete _player;
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
					if (init)
						_player = new Pacman({rect.x, rect.y});
					*c_it = Entity::Empty;
					break;
				// Replace this case by subtyping polymorphism
				case Entity::Ghost:
					if (init) {
						point_t pos = {rect.x, rect.y};

						if (_ghosts.size() == 0)
							_ghosts.push_back(new Blinky(pos));
						else if (_ghosts.size() == 1)
							_ghosts.push_back(new Inky(pos));
						else if (_ghosts.size() == 2)
							_ghosts.push_back(new Clyde(pos));
						else if (_ghosts.size() == 3)
							_ghosts.push_back(new Pinky(pos));
					}
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
	rect.x = _player->get_pos().x;
	rect.y = _player->get_pos().y;
	SDL_SetRenderDrawColor(_renderer, (Colors::Pacman >> 16) & 0xff, (Colors::Pacman >> 8) & 0xff, Colors::Pacman & 0xff, 255);
	SDL_RenderDrawRect(_renderer, &rect);
	SDL_RenderFillRect(_renderer, &rect);
	// Need to draw ghosts
	
	for (size_t i = 0; i < _ghosts.size(); i++) {
		Colors::Colors color = _ghosts[i]->get_color();

		rect.x = _ghosts[i]->get_pos().x;
		rect.y = _ghosts[i]->get_pos().y;
		SDL_SetRenderDrawColor(_renderer, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, 255);
		SDL_RenderDrawRect(_renderer, &rect);
		SDL_RenderFillRect(_renderer, &rect);
	}
	SDL_RenderPresent(_renderer);
}

void Game::_update_player_map_pos(void) {
	_map[_player->get_pos().y / TILE_SIZE][_player->get_pos().x / TILE_SIZE] = Entity::Pacman;
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
		if (_check_collisions())
			_player->move(_player->get_pos());
		_update_player_map_pos();
		_draw_map(false);
		while (SDL_PollEvent(&_ev)) {
			switch (_ev.type) {
				case SDL_QUIT:
					run = false;
					break;
				case SDL_KEYDOWN:
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
	// Make pacman change direction automatically when it can
	// In the future I will need to check for ghost position and state
	switch (_ev.key.keysym.sym) {
		case SDLK_UP:
			_player->next_dir = Directions::UP;
			break;
		case SDLK_DOWN:
			_player->next_dir = Directions::DOWN;
			break;
		case SDLK_LEFT:
			_player->next_dir = Directions::LEFT;
			break;
		case SDLK_RIGHT:
			_player->next_dir = Directions::RIGHT;
			break;
		default:
			break;
	}
}

bool Game::_check_collisions(void) const {
	point_t new_pos = _player->get_pos();
	bool result = false;

	if (_player->next_dir != _player->dir) {
		switch (_player->next_dir) {
			case Directions::UP:
				new_pos.y -= VELOCITY;
				break;
			case Directions::DOWN:
				new_pos.y += VELOCITY;
				break;
			case Directions::LEFT:
				new_pos.x -= VELOCITY;
				break;
			case Directions::RIGHT:
				new_pos.x += VELOCITY;
				break;
			default:
				break;
		}
		if (_map[new_pos.y / TILE_SIZE][new_pos.x / TILE_SIZE] != Entity::Wall
			&& _map[(new_pos.y - 1) / TILE_SIZE + 1][new_pos.x / TILE_SIZE] != Entity::Wall
			&& _map[new_pos.y / TILE_SIZE][(new_pos.x - 1) / TILE_SIZE + 1] != Entity::Wall
			&& _map[(new_pos.y - 1)/ TILE_SIZE + 1][(new_pos.x - 1) / TILE_SIZE + 1] != Entity::Wall) {
			_player->dir = _player->next_dir;
			return true;
		}
	}
	new_pos = _player->get_pos();
	switch (_player->dir) {
		case Directions::UP:
			new_pos.y -= VELOCITY;
			break;
		case Directions::DOWN:
			new_pos.y += VELOCITY;
			break;
		case Directions::LEFT:
			new_pos.x -= VELOCITY;
			break;
		case Directions::RIGHT:
			new_pos.x += VELOCITY;
			break;
		default:
			break;
	}
	result = _map[new_pos.y / TILE_SIZE][new_pos.x / TILE_SIZE] != Entity::Wall
		&& _map[(new_pos.y - 1) / TILE_SIZE + 1][new_pos.x / TILE_SIZE] != Entity::Wall
		&& _map[new_pos.y / TILE_SIZE][(new_pos.x - 1) / TILE_SIZE + 1] != Entity::Wall
		&& _map[(new_pos.y - 1)/ TILE_SIZE + 1][(new_pos.x - 1) / TILE_SIZE + 1] != Entity::Wall;
	return result;
}
