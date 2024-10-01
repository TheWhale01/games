#include "Pacman.hpp"
#include "pacman.hpp"

Pacman::Pacman(point_t const &pos): AGhost(Colors::Pacman, pos),
	dir(Directions::LEFT), next_dir(dir) {}
Pacman::~Pacman(void) {}

void Pacman::check_borders(int w, int h) {
	std::cout << "DEBUG: " << _pos.x << ", " << _pos.y << std::endl;
	if (_pos.x + TILE_SIZE > w)
		_pos.x = 0;
	else if (_pos.x <= 0)
		_pos.x = w - TILE_SIZE;
	else if (_pos.y + TILE_SIZE > h)
		_pos.y = 0;
	else if (_pos.y <= 0)
		_pos.y = h;
}

void Pacman::move(const point_t &pacman_pos) {
	static_cast<void>(pacman_pos);
	switch (dir) {
		case Directions::UP:
			_pos.y -= VELOCITY;
			break;
		case Directions::DOWN:
			_pos.y += VELOCITY;
			break;
		case Directions::LEFT:
			_pos.x -= VELOCITY;
			break;
		case Directions::RIGHT:
			_pos.x += VELOCITY;
			break;
		default:
			break;
	}
}
