#include "Game.hpp"

namespace Daklit
{
	//public:
	Game::Game() : m_window("Pong", sf::Vector2u(800, 600)), m_ballSize(sf::Vector2f(10, 10)),
		m_ballAngle(0), m_paddleSize(sf::Vector2f(25, 100)), m_increment(400)
	{
		srand(time(nullptr));
		Setup();
	}
	Game::~Game() {}

	void Game::Setup()
	{
		ResetAngle();

		m_ball.setSize(m_ballSize - sf::Vector2f(3, 3));
		m_ball.setOutlineThickness(3);
		m_ball.setOutlineColor(sf::Color::Red);
		m_ball.setOrigin(m_ball.getPosition().x / 2.f, m_ball.getPosition().y / 2.f);
		m_ball.setPosition(sf::Vector2f(m_window.GetWindowSize().x / 2.f, m_window.GetWindowSize().y / 2.f));

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

		m_font.loadFromFile("assets/Inconsolata-Bold.ttf");
		m_pauseMessage.setFont(m_font);
		m_pauseMessage.setCharacterSize(40);
		m_pauseMessage.setPosition(100.f, 150.f);
		m_pauseMessage.setFillColor(sf::Color::White);
		m_pauseMessage.setString("\t\t SFML Pong!\nPress space to start the game");
	}

	void Game::Reset()
	{
		srand(time(nullptr));
		ResetAngle();
		m_increment = 400;

		m_elapsed = m_clock.restart();
		m_ball.setPosition(sf::Vector2f(m_window.GetWindowSize().x / 2.f, m_window.GetWindowSize().y / 2.f));
		m_leftPaddle.setPosition(sf::Vector2f(m_paddleSize.x / 2.f + 10, 300));
		m_rightPaddle.setPosition(sf::Vector2f(m_window.GetWindowSize().x - m_paddleSize.x / 2.f - 7, 300));
	}

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

		MoveBall();
	}
	void Game::Update()
	{
		m_window.Update();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Reset();
		}
	}
	void Game::Render()
	{
		//clear screen
		m_window.BeginDraw(sf::Color(0xff, 0xC3, 0x0F));

		m_window.Draw(m_ball);
		m_window.Draw(m_leftPaddle);
		m_window.Draw(m_rightPaddle);
		// Display.
		m_window.EndDraw();
	}
	void Game::Pause()
	{
		//clear screen
		m_window.BeginDraw(sf::Color(0xff, 0xff, 0x0F));
		m_window.Draw(m_pauseMessage);
		m_window.EndDraw();
	}
	Window* Game::GetWindow()
	{
		return&m_window;
	}

	void Game::ResetAngle()
	{
		do
		{
			m_ballAngle = (std::rand() % 360) * 2 * pi / 360;
		} while (std::abs(std::cos(m_ballAngle)) < 0.9f);
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
			m_window.notPlaying();

			//wall bounce
			/*if (m_ball.getPosition().y > m_rightPaddle.getPosition().y)
				m_ballAngle = pi - m_ballAngle - (std::rand() % 20) * pi / 180;
			else
				m_ballAngle = pi - m_ballAngle + (std::rand() % 20) * pi / 180;*/
		}
		// right wall
		if (m_ball.getPosition().x + m_ballSize.x > m_window.GetWindowSize().x)
		{
			m_window.notPlaying();

			//wall bounce
			/*if (m_ball.getPosition().y > m_leftPaddle.getPosition().y)
				m_ballAngle = pi - m_ballAngle - (std::rand() % 20) * pi / 180;
			else
				m_ballAngle = pi - m_ballAngle + (std::rand() % 20) * pi / 180;*/
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
			m_increment += 10;
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
			m_increment += 10;
		}

		float distance = m_increment * m_elapsed.asSeconds();
		m_ball.move(std::cos(m_ballAngle) * distance, std::sin(m_ballAngle) * distance);
	}
}