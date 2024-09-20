#pragma once
#include "pacman.hpp"
#include "AGhost.hpp"

class Blinky : public AGhost {
	public:
		Blinky(void);
		~Blinky(void);

	private:
		void _move(const point_t &pacman_pos);
};
