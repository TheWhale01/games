#pragma once
#include "AGhost.hpp"

class Pacman : public AGhost {
	public:
		Pacman(point_t const &pos);
		~Pacman(void);

		void move(point_t const &pacman_pos);
		void set_way(bool way);
		void set_direction(int direction);
		void set_next_pos(void);
		point_t const &get_next_pos(void) const;
	private:
		bool _way;
		int _direction;
		point_t _next_pos;
};
