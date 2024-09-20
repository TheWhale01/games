#pragma once
#include "pacman.hpp"
#include "AGhost.hpp"

class Pinky : public AGhost {
	public:
		Pinky(void);
		~Pinky(void);

	private:
		void _move(const point_t &pacman_pos);
};
