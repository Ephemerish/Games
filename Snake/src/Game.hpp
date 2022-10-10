#pragma once
#include "Window.hpp"
#include "World.hpp"
#include "Snake.hpp"
#include "Textbox.hpp"

namespace Snake
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
		Textbox m_textbox;
	};
}