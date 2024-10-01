#pragma once
#include "pacman.hpp"
#include "AGhost.hpp"

class Pacman : public AGhost {
	public:
		Pacman(point_t const &pos);
		~Pacman(void);

		int dir;
		int next_dir;
	
		void move(point_t const &pacman_pos);
		void update_dir(void);
		void check_borders(int w, int h);
};
