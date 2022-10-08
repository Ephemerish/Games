#pragma once
#include "Window.hpp"
#include "World.hpp"
#include "Snake.hpp"

namespace Daklit
{
	class Game
	{
	public:
		Game();
		~Game();

		void HandleInput();
		void Update();
		void Render();

		sf::Time GetElapsed();
		void RestartClock();

		Window* GetWindow();
	private:
		sf::Clock m_clock;
		float m_elapsed;

		Window m_window;
		World m_world;
		Snake m_snake;
	};
}