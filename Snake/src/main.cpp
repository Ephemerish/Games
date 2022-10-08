#include "Game.hpp"
#include <windows.h>
int main(int argc, char** argv[])
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	Daklit::Game game;
	while (!game.GetWindow()->IsDone())
	{
		sf::sleep(sf::seconds(0.05f));
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}
	return 0;
}