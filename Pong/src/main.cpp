#include "Game.hpp"
#include <windows.h>

void main(int argc, char** argv[])
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	Daklit::Game game;
	while (!game.GetWindow()->IsDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
		sf::sleep(sf::seconds(0.002));
		game.RestartClock();
	}
}