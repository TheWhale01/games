#include "pacman.hpp"
#include "Game.hpp"
#include "Blinky.hpp"
#include "Inky.hpp"
#include "Clyde.hpp"
#include "Pinky.hpp"

Game::GameException::GameException(const char *str): _str(str) {}
Game::GameException::GameException(std::string const &str): _str(str.c_str()) {}
Game::GameException::~GameException(void) {}

const char *Game::GameException::what(void) const throw() {
	return _str;
}

Game::Game(const char *map_path): _window(nullptr), _renderer(nullptr), _w_height(0),
	_w_width(0), _run(true),  _player(nullptr) {
	_ghosts.reserve(4);
	if (!_load_map(map_path))
		throw GameException("Non valid map");
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0
	|| !(_window = SDL_CreateWindow("Pacman", 0, 0, _w_width, _w_height, SDL_WINDOW_SHOWN))
	|| !(_renderer = SDL_CreateRenderer(_window, 0, 0))) {
		std::string str = "Error initializing SDL: ";
		str += SDL_GetError();
		throw Game::GameException(str);
	}
	_draw_map();
}

Game::~Game(void) {
	for (size_t i = 0; i < _ghosts.size(); i++)
		if (_ghosts[i])
			delete _ghosts[i];
	if (_player)
		delete _player;
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
	_window = nullptr;
	_renderer = nullptr;
}

void Game::_draw_rect(SDL_Rect const &rect, int color) {
	SDL_SetRenderDrawColor(_renderer, (color >> 16) & 0xff,
			(color >> 8) & 0xff, color & 0xff, 255);
	SDL_RenderDrawRect(_renderer, &rect);
	SDL_RenderFillRect(_renderer, &rect);
}

void Game::_draw_ghosts(void) {
	SDL_Rect rect;

	rect.w = TILE_SIZE, rect.h = TILE_SIZE;
	for (size_t i = 0; i < _ghosts.size(); i++) {
		rect.x = _ghosts[i]->get_pos().x,
			rect.y = _ghosts[i]->get_pos().y;
		_draw_rect(rect, _ghosts[i]->get_color());
	}
}

void Game::_draw_pacman(void) {
	SDL_Rect rect = {_player->get_pos().x, _player->get_pos().y,
		TILE_SIZE, TILE_SIZE};
	_draw_rect(rect, _player->get_color());
}

bool Game::_load_map(const char *map_path) {
	std::ifstream mapfile;
	std::string line;
	point_t pos = {0, 0};

	mapfile.open(map_path);
	for (size_t nb_line = 0; getline(mapfile, line); nb_line++) {
		_map.push_back(line);
		_w_width = std::max(static_cast<size_t>(_w_width),
		      _map[_map.size() - 1].size() * TILE_SIZE);
		_w_height += TILE_SIZE;
		for (size_t i = 0; i < line.size(); i++) {
			pos.x = i * TILE_SIZE;
			pos.y = nb_line * TILE_SIZE;
			if (line[i] == Entity::Ghost) {
				// Don't like this
				if (_ghosts.size() == 0)
					_ghosts.push_back(new Blinky(pos));
				else if (_ghosts.size() == 1)
					_ghosts.push_back(new Inky(pos));
				else if (_ghosts.size() == 2)
					_ghosts.push_back(new Clyde(pos));
				else if (_ghosts.size() == 3)
					_ghosts.push_back(new Pinky(pos));
			}
			else if (line[i] == Entity::Pacman)
				_player = new Pacman(pos);
		}
	}
	mapfile.close();
	return !_map.empty();
}

void Game::_draw_map() {
	SDL_Rect rect = {0, 0, TILE_SIZE, TILE_SIZE};
	int color = Colors::Empty;

	for(size_t i = 0; i < _map.size(); i++) {
		for (size_t j = 0; j < _map[i].size(); j++) {
			switch (_map[i][j]) {
				case Entity::Wall:
					color = Colors::Wall;
					break;
				case Entity::Fruit:
					color = Colors::Fruit;
					break;
				case Entity::Dot:
					color = Colors::Dot;
					break;
				default:
					color = Colors::Empty;
					break;
			}
			_draw_rect(rect, color);
			rect.x += TILE_SIZE;
		}
		rect.x = 0;
		rect.y += TILE_SIZE;
	}
	_draw_ghosts();
	_draw_pacman();
	SDL_RenderPresent(_renderer);
}

void Game::_update_player_map_pos(void) {
	point_t pos = {_player->get_pos().x / TILE_SIZE, _player->get_pos().y / TILE_SIZE};

	if (_player->get_pos().y % TILE_SIZE == 0
		&& _player->get_pos().x % TILE_SIZE == 0
		&& (_map[pos.y][pos.x] == Entity::Dot || _map[pos.y][pos.x] == Entity::Fruit))
		_map[pos.y][pos.x] = Entity::Pacman;
}

int Game::loop(void) {
	int		frame_time;
	Uint32		frame_start;
	const int	frame_delay = 1000 / FPS;

	frame_time = 0;
	frame_start = 0;
	while (_run) {
		frame_start = SDL_GetTicks();
		if (_check_ghosts_collisions())
			return EXIT_FAILURE;
		if (_check_collisions()) {
			_player->move(_player->get_pos());
			_player->check_borders(_w_width, _w_height);
		}
		_draw_map();
		_update_player_map_pos();
		std::cout << "pos_x: " << _player->get_pos().x << std::endl << "pos_y: " << _player->get_pos().y << std::endl << std::endl;
		while (SDL_PollEvent(&_ev)) {
			switch (_ev.type) {
				case SDL_QUIT:
					_run = false;
					break;
				case SDL_KEYDOWN:
					_handle_key();
					break;
				default:
					break;
			}
		}
		if (_run) {
			frame_time = SDL_GetTicks() - frame_start;
			if (frame_delay > frame_time)
				SDL_Delay(frame_delay - frame_time);
		}
	}
	return EXIT_SUCCESS;
}

void Game::_handle_key(void) {
	// In the future I will need to check for ghost position and state
	switch (_ev.key.keysym.sym) {
		case SDLK_w:
		case SDLK_UP:
			_player->next_dir = Directions::UP;
			break;
		case SDLK_s:
		case SDLK_DOWN:
			_player->next_dir = Directions::DOWN;
			break;
		case SDLK_a:
		case SDLK_LEFT:
			_player->next_dir = Directions::LEFT;
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			_player->next_dir = Directions::RIGHT;
			break;
		default:
			break;
	}
}

bool Game::_check_walls(const point_t &pos) const {
	return _map[pos.y / TILE_SIZE][pos.x / TILE_SIZE] != Entity::Wall
		&& _map[(pos.y - 1) / TILE_SIZE + 1][pos.x / TILE_SIZE] != Entity::Wall
		&& _map[pos.y / TILE_SIZE][(pos.x - 1) / TILE_SIZE + 1] != Entity::Wall
		&& _map[(pos.y - 1)/ TILE_SIZE + 1][(pos.x - 1) / TILE_SIZE + 1] != Entity::Wall;
}

point_t Game::_get_new_pos(point_t const &base_pos, int direction) const {
	point_t new_pos = base_pos;

	switch (direction) {
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
	return new_pos;
}

bool Game::_check_collisions(void) const {
	point_t new_pos;

	if (_player->next_dir != _player->dir) {
			new_pos = _get_new_pos(_player->get_pos(), _player->next_dir);
			if (_check_walls(new_pos)) {
				_player->dir = _player->next_dir;
				return true;
		}
	}
	new_pos = _get_new_pos(_player->get_pos(), _player->dir);
	return _check_walls(new_pos);
}

bool Game::_check_ghosts_collisions(void) const {
	return _map[_player->get_pos().y / TILE_SIZE][_player->get_pos().x / TILE_SIZE] == Entity::Ghost
		&& _map[(_player->get_pos().y - 1) / TILE_SIZE + 1][_player->get_pos().x / TILE_SIZE] == Entity::Ghost
		&& _map[_player->get_pos().y / TILE_SIZE][(_player->get_pos().x - 1) / TILE_SIZE + 1] == Entity::Ghost
		&& _map[(_player->get_pos().y - 1)/ TILE_SIZE + 1][(_player->get_pos().x - 1) / TILE_SIZE + 1] == Entity::Ghost;
}
