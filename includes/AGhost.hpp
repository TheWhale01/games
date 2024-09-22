#pragma once
#include "pacman.hpp"

class AGhost {
	public:
		AGhost(Colors::Colors const &color, point_t const &pos);
		virtual ~AGhost(void);

		const point_t &get_pos(void) const;
		const EntityState::EntityState &get_state(void) const;
		const Colors::Colors &get_color(void) const;

		virtual void move(const point_t &pacman_pos) = 0;
	protected:
		point_t				_pos;
		EntityState::EntityState	_state;
		Colors::Colors			_color;
};
