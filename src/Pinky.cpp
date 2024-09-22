#include "pacman.hpp"
#include "Pinky.hpp"

Pinky::Pinky(point_t const &pos): AGhost(Colors::Pinky, pos) {}
Pinky::~Pinky(void) {}

void Pinky::move(const point_t &pacman_pos) {
	(void)pacman_pos;
}
