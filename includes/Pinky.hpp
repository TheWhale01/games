#pragma once
#include "pacman.hpp"
#include "AGhost.hpp"

class Pinky : public AGhost {
	public:
		Pinky(point_t const &pos);
		~Pinky(void);

		void move(const point_t &pacman_pos);
	private:
};
