#include "pacman.hpp"
#include "Clyde.hpp"

Clyde::Clyde(point_t const &pos): AGhost(Colors::Clyde, pos) {}
Clyde::~Clyde(void) {}

void Clyde::_move(const point_t &pacman_pos) {
	(void)pacman_pos;
}
