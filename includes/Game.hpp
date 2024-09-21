#pragma once
#include "pacman.hpp"
#include "AGhost.hpp"

#define TILE_SIZE 32
#define VELOCITY 32
#define FPS 60

class Game {
	public:
		Game(const char *map_path);
		~Game();
	
		void loop(void);
	
	private:
		SDL_Window *_window;
		SDL_Renderer *_renderer;
		SDL_Event _ev;
		size_t _w_height;
		size_t _w_width;
		point_t _player;
		std::vector<std::string> _map;
		std::vector<AGhost*> _ghosts;

		void _load_map(const char *map_path);
		void _draw_map(bool init);
		void _update_player_map_pos(void);
		void _handle_key(void);
};
