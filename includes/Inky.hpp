#pragma once
#include "pacman.hpp"
#include "AGhost.hpp"

class Inky : public AGhost {
	public:
		Inky(void);
		~Inky(void);

	private:
		void _move(const point_t &pacman_pos);
};
