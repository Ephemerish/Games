#include "Game.hpp"

int main(int argc, char** argv[])
{
	Daklit::Game game;
	while (!game.GetWindow()->IsDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
		sf::sleep(sf::seconds(0.002));
		game.RestartClock();
	}
	return 0;
}