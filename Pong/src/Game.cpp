#include "Game.hpp"

namespace Daklit
{
//public:
	Game::Game() : m_window("Pong", sf::Vector2u(800, 600)), m_ballSize(sf::Vector2f(10,10)),
		m_ballAngle(0.1f), m_paddleSize(sf::Vector2f(25, 100))
	{
		m_ball = sf::RectangleShape(m_ballSize - sf::Vector2f(3, 3));
		m_ball.setOutlineThickness(3);
		m_ball.setOutlineColor(sf::Color::Red);
		m_ball.setOrigin(m_ball.getPosition().x / 2, m_ball.getPosition().y / 2);
		m_ball.setPosition(sf::Vector2f(400, 300));

		m_leftPaddle.setSize(m_paddleSize - sf::Vector2f(3, 3));
		m_leftPaddle.setOutlineThickness(3);
		m_leftPaddle.setOutlineColor(sf::Color::Black);
		m_leftPaddle.setFillColor(sf::Color(100, 100, 200));
		m_leftPaddle.setOrigin(m_paddleSize / 2.f); 
		m_leftPaddle.setPosition(sf::Vector2f(m_paddleSize.x / 2.f + 10, 300));

		m_rightPaddle.setSize(m_paddleSize - sf::Vector2f(3, 3));
		m_rightPaddle.setOutlineThickness(3);
		m_rightPaddle.setOutlineColor(sf::Color::Black);
		m_rightPaddle.setFillColor(sf::Color(200, 100, 100));
		m_rightPaddle.setOrigin(m_paddleSize / 2.f);
		m_rightPaddle.setPosition(sf::Vector2f(m_window.GetWindowSize().x - m_paddleSize.x / 2.f - 7, 300));
	}
	Game::~Game() {}

	void Game::HandleInput()
	{
	//left Paddle
		float distance = 400 * m_elapsed.asSeconds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			(m_leftPaddle.getPosition().y - m_paddleSize.y / 2 > 8))
		{
			m_leftPaddle.move(0.f, -distance);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
			(m_leftPaddle.getPosition().y + m_paddleSize.y / 2 < m_window.GetWindowSize().y - 5))
		{
			m_leftPaddle.move(0.f, distance);
		}
	//right Paddle
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
			(m_rightPaddle.getPosition().y - m_paddleSize.y / 2 > 8))
		{
			m_rightPaddle.move(0.f, -distance);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
			(m_rightPaddle.getPosition().y + m_paddleSize.y / 2 < m_window.GetWindowSize().y - 5))
		{
			m_rightPaddle.move(0.f, distance);
		}
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
		m_window.Draw(m_leftPaddle);
		m_window.Draw(m_rightPaddle);
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

	// left wall
		if (m_ball.getPosition().x - m_ballSize.x < 0.f)
		{
			//m_window.Done();

			if (m_ball.getPosition().y > m_rightPaddle.getPosition().y)
				m_ballAngle = pi - m_ballAngle - (std::rand() % 20) * pi / 180;
			else
				m_ballAngle = pi - m_ballAngle + (std::rand() % 20) * pi / 180;
		}
	// right wall
		if (m_ball.getPosition().x + m_ballSize.x > m_window.GetWindowSize().x)
		{
			//m_window.Done();

			if (m_ball.getPosition().y > m_leftPaddle.getPosition().y)
				m_ballAngle = pi - m_ballAngle - (std::rand() % 20) * pi / 180;
			else
				m_ballAngle = pi - m_ballAngle + (std::rand() % 20) * pi / 180;

		}
	// ceiling
		if (m_ball.getPosition().y - m_ballSize.y < 0.f)
		{
			m_ballAngle = -m_ballAngle;
			m_ball.setPosition(m_ball.getPosition().x, m_ballSize.x + 0.1f);
		}
	// floor
		if (m_ball.getPosition().y + m_ballSize.y > m_window.GetWindowSize().y)
		{
			m_ballAngle = -m_ballAngle;
			m_ball.setPosition(m_ball.getPosition().x, m_window.GetWindowSize().y - m_ballSize.y - 0.1f);
		}

	// left paddle
		if (m_ball.getPosition().x - m_ballSize.x < m_leftPaddle.getPosition().x + m_paddleSize.x / 2 &&
			m_ball.getPosition().x - m_ballSize.x > m_leftPaddle.getPosition().x &&
			m_ball.getPosition().y + m_ballSize.y >= m_leftPaddle.getPosition().y - m_paddleSize.y / 2 &&
			m_ball.getPosition().y - m_ballSize.y <= m_leftPaddle.getPosition().y + m_paddleSize.y / 2)
		{
			if (m_ball.getPosition().y > m_leftPaddle.getPosition().y)
				m_ballAngle = pi - m_ballAngle + (std::rand() % 20) * pi / 180;
			else
				m_ballAngle = pi - m_ballAngle - (std::rand() % 20) * pi / 180;

			m_ball.setPosition(m_leftPaddle.getPosition().x + m_ballSize.x + m_paddleSize.x / 2 + 0.1f, m_ball.getPosition().y);
		}
	// right paddle
		if (m_ball.getPosition().x + m_ballSize.x > m_rightPaddle.getPosition().x - m_paddleSize.x / 2 &&
			m_ball.getPosition().x + m_ballSize.x < m_rightPaddle.getPosition().x &&
			m_ball.getPosition().y + m_ballSize.y >= m_rightPaddle.getPosition().y - m_paddleSize.y / 2 &&
			m_ball.getPosition().y - m_ballSize.y <= m_rightPaddle.getPosition().y + m_paddleSize.y / 2)
		{
			if (m_ball.getPosition().y > m_rightPaddle.getPosition().y)
				m_ballAngle = pi - m_ballAngle + (std::rand() % 20) * pi / 180;
			else
				m_ballAngle = pi - m_ballAngle - (std::rand() % 20) * pi / 180;

			m_ball.setPosition(m_rightPaddle.getPosition().x - m_ballSize.x - m_paddleSize.x / 2 - 0.1f, m_ball.getPosition().y);
		}

		float distance = 400 * m_elapsed.asSeconds();
		m_ball.move(std::cos(m_ballAngle) * distance, std::sin(m_ballAngle) * distance);
	}
}