#pragma once
#include "Text.hpp"
#include <cstdlib>

const double pi = 3.14159f;

namespace Daklit
{
	class Game
	{
	public:
		Game();
		~Game();

		void Setup();
		void Reset();

		void HandleInput();
		void Update();
		void Render();
		void Pause();
		Window* GetWindow();

		void ResetAngle();

		sf::Time GetElapsed();
		void RestartClock();
	private:
		sf::Vector2f m_paddleSize;
		sf::Vector2f m_ballStartPosition;
		sf::Vector2f m_leftPaddleStartPosition;
		sf::Vector2f m_rightPaddleStartPosition;

		sf::Vector2f m_ballSize;
		float m_ballAngle;

		sf::RectangleShape m_ball;
		sf::RectangleShape m_leftPaddle;
		sf::RectangleShape m_rightPaddle;

		float m_increment;

		sf::Clock m_clock;
		sf::Time m_elapsed;

		void MoveBall();
		Window m_window;
	};
}
