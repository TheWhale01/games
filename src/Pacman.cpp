#include "Pacman.hpp"
#include "pacman.hpp"

Pacman::Pacman(point_t const &pos): AGhost(Colors::Pacman, pos),
	dir(Directions::LEFT), next_dir(dir) {}
Pacman::~Pacman(void) {}

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
