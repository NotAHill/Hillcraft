#include "Game.h"

int main()
{
	// (gci -include *.cpp, *.h -recurse | select-string .).Count
	Game game({ 1280, 640 }, "Project", 0);
	game.run();
	return 0;
}