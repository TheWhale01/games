#include "Pacman.hpp"
#include "pacman.hpp"

Pacman::Pacman(point_t const &pos): AGhost(Colors::Pacman, pos), _way(true),
	_direction(1), _next_pos(pos) {
	set_next_pos();
}
Pacman::~Pacman(void) {}

void Pacman::set_way(bool way) { _way = way; }
void Pacman::set_direction(int direction) { _direction = direction; }
point_t const &Pacman::get_next_pos(void) const { return _next_pos; }

void Pacman::move(const point_t &pacman_pos) {
	static_cast<void>(pacman_pos);
	_pos = _next_pos;
}

void Pacman::set_next_pos(void) {
	_next_pos = _pos;
	if (_way)
		_next_pos.x += VELOCITY * _direction;
	else
		_next_pos.y += VELOCITY * _direction;
}
