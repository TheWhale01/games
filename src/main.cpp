#include "pacman.hpp"
#include "Game.hpp"

int	main(int ac, char** av)
{
	(void) ac;
	(void) av;

	// Don't like this
	try {
		Game game(av[1]);
		return game.loop();
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return EXIT_FAILURE;
} 
