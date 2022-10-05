#include "Game.hpp"
#include <windows.h>

int main(int argc, char** argv[])
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	Daklit::Game game;
	while (!game.GetWindow()->IsDone())
	{
		
		game.Update();
		if(game.GetWindow()->IsPlaying())
		{
			game.HandleInput();
			game.Render();
			sf::sleep(sf::seconds(0.002f));
			game.RestartClock();
		}
		if (!game.GetWindow()->IsPlaying())
		{
			sf::sleep(sf::seconds(0.1f));
			game.Pause();
		}
	}

	return 0;
}