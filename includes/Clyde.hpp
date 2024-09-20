#pragma once
#include "pacman.hpp"
#include "AGhost.hpp"

class Clyde : public AGhost {
	public:
		Clyde(void);
		~Clyde(void);

	private:
		void _move(const point_t &pacman_pos);
};
