#pragma once
#include "pacman.hpp"
#include "AGhost.hpp"
#include "Pacman.hpp"

class Game {
	public:
		Game(const char *map_path);
		~Game();
	
		void loop(void);
	
	private:
		SDL_Window *_window;
		SDL_Renderer *_renderer;
		SDL_Event _ev;
		int _w_height;
		int _w_width;
		bool _run;
		Pacman *_player;
		std::vector<std::string> _map;
		std::vector<AGhost*> _ghosts;

		void _load_map(const char *map_path);
		void _draw_map();
		void _draw_ghosts();
		void _draw_pacman();
		void _draw_rect(SDL_Rect const &rect, int color);
		void _update_player_map_pos(void);
		void _handle_key(void);
		bool _check_collisions(void) const;
		bool _check_walls(const point_t &pos) const;
		point_t _get_new_pos(point_t const &base_pos, int direction) const ;
};
