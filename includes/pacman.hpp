#pragma once
#include <SDL_render.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_video.h>
#include <fstream>

#define RGB_R 16
#define RGB_G 8
#define RGB_B 0

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

namespace EntityState {
	enum EntityState {
		Normal,
		Afraid
	};
}
