#include "pacman.hpp"
#include "Inky.hpp"

Inky::Inky(point_t const &pos): AGhost(Colors::Inky, pos) {}
Inky::~Inky(void) {}

void Inky::move(const point_t &pacman_pos) {
	(void)pacman_pos;
}
