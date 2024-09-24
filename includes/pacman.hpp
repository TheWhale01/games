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

#define TILE_SIZE 32
#define VELOCITY 4
#define FPS 60

#define RGB_R 16
#define RGB_G 8
#define RGB_B 0

typedef struct {
	int x;
	int y;
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
		Fruit = 0xdea185,
		Dot = 0xdea185,
		Pacman = 0xffff00,
		Empty = 0x000000,
		Blinky = 0xff0000,
		Pinky = 0xffb8ff,
		Inky = 0x00ffff,
		Clyde = 0xffb852
	};
}

namespace EntityState {
	enum EntityState {
		Normal,
		Afraid
	};
}

namespace Directions {
	enum Directions {
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};
}

