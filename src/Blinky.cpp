#include "pacman.hpp"
#include "Blinky.hpp"

Blinky::Blinky(point_t const &pos): AGhost(Colors::Blinky, pos) {}
Blinky::~Blinky(void) {}

void Blinky::_move(const point_t &pacman_pos) {
	(void)pacman_pos;
}
