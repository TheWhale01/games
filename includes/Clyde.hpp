#pragma once
#include "pacman.hpp"
#include "AGhost.hpp"

class Clyde : public AGhost {
	public:
		Clyde(point_t const &pos);
		~Clyde(void);

		void move(const point_t &pacman_pos);
	private:
};
