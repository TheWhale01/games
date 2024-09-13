#pragma once
#include "pacman.hpp"

# define TILE_SIZE 48

typedef struct {
	size_t x;
	size_t y;
} point_t;

namespace Entity {
	enum Entity {
		Wall = '#',
		Fruit = '@',
		Dot = '*',
		Pacman = 'C',
		Ghost = 'M',
		Empty = ' '
	};
} 

namespace Colors {
	enum Colors {
		Wall = 0x1919a6,
		Fruit = 0xeea185,
		Dot = 0xdea185,
		Pacman = 0xffff00,
		Ghost = 0xfd0000,
		Empty = 0x000000,
	};
}

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
		std::vector<std::string> _map;

		void _load_map(const char *map_path);
		void _draw_map(void);
};
