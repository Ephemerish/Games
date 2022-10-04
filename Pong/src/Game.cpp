#include "Game.hpp"

namespace Daklit
{
//public:
	Game::Game() : m_window("Pong", sf::Vector2u(800, 600)), m_ballSize(sf::Vector2f(10,10)), m_ballAngle(0.1f)
	{
		m_ball = sf::RectangleShape(m_ballSize);
		m_ball.setOrigin(m_ball.getPosition().x / 2, m_ball.getPosition().y / 2);
		m_ball.setPosition(sf::Vector2f(400, 300));
		m_increment = sf::Vector2i(200, 200);;
	}
	Game::~Game() {}

	void Game::HandleInput()
	{

	}
	void Game::Update()
	{
		m_window.Update();
		MoveBall();
	}
	void Game::Render()
	{
		//clear screen
		m_window.BeginDraw();
		m_window.Draw(m_ball);
		// Display.
		m_window.EndDraw(); 
	}
	Window* Game::GetWindow()
	{ 
		return& m_window; 
	}

	sf::Time Game::GetElapsed()
	{
		return m_elapsed;
	}
	void Game::RestartClock()
	{
		m_elapsed = m_clock.restart();
	}
//private:
	
	void Game::MoveBall()
	{
		sf::Vector2u l_windowSize = m_window.GetWindowSize();
		sf::Vector2f l_textureSize = m_ballSize;

		if ((m_ball.getPosition().x > l_windowSize.x - l_textureSize.x && m_increment.x > 0) ||
			(m_ball.getPosition().x < 0 && m_increment.x < 0))
		{
			m_increment.x = -m_increment.x;
		}

		if ((m_ball.getPosition().y > l_windowSize.y - l_textureSize.x && m_increment.y > 0) ||
			(m_ball.getPosition().y < 0 && m_increment.y < 0))
		{
			m_increment.y = -m_increment.y;
		}

		float fElapsed = m_elapsed.asSeconds();
		m_ball.setPosition(
			m_ball.getPosition().x + (m_increment.x * fElapsed),
			m_ball.getPosition().y + (m_increment.y * fElapsed)
		);
	}
}