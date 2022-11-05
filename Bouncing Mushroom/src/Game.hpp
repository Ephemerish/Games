#pragma once
#include "Window.hpp"

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
		Window* GetWindow();

		sf::Time GetElapsed();
		void RestartClock();
	private:
		sf::Texture m_mushroomTexture;
		sf::Sprite m_mushroom;
		sf::Vector2f m_increment;

		sf::Clock m_clock;
		sf::Time m_elapsed;

		void MoveMushroom();
		Window m_window;
	};
}