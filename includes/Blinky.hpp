#pragma once
#include "pacman.hpp"
#include "AGhost.hpp"

class Blinky : public AGhost {
	public:
		Blinky(point_t const &pos);
		~Blinky(void);

		void move(const point_t &pacman_pos);
	private:
};
