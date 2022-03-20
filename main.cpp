#include "Game.h"

int main()
{
	// (gci -include *.cpp, *.h, *.glsl -recurse | select-string .).Count
	Game game({ 1280, 640 }, "Project", false);
	game.run();
	return 0;
}