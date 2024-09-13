#include "pacman.hpp"
#include "Game.hpp"

int	main(int ac, char** av)
{
	Game game(av[1]);

	(void) ac;
	(void) av;
	game.loop();
} 
