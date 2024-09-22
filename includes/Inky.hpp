#pragma once
#include "pacman.hpp"
#include "AGhost.hpp"

class Inky : public AGhost {
	public:
		Inky(point_t const &pos);
		~Inky(void);

		void move(const point_t &pacman_pos);
	private:
};
