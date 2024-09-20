#pragma once
#include "pacman.hpp"

class AGhost {
	public:
		AGhost(void);
		~AGhost(void);

		const point_t &get_pos(void) const;
		const EntityState::EntityState &get_state(void) const;
	private:
		point_t				_pos;
		EntityState::EntityState	_state;

		virtual void _move(const point_t &pacman_pos) = 0;
};
