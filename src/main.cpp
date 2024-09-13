#include "pacman.hpp"
#include "Game.hpp"

int	main(int ac, char** av)
{
	Game game;

	(void) ac;
	(void) av;
	game.loop();
} 
