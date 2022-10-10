#include "Game.hpp"

namespace Snake
{
	//public:
	Game::Game() : m_window("Snake", sf::Vector2u(800, 600)),
		m_snake(m_world.GetBlockSize()), m_world(sf::Vector2u(800, 600))
	{
		m_clock.restart();
		srand(time(nullptr));

		m_elapsed = 0.0f;
	}
	Game::~Game() {}

	void Game::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_snake.GetDirection() != Direction::Down)
		{
			m_snake.SetDirection(Direction::Up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_snake.GetDirection() != Direction::Up)
		{
			m_snake.SetDirection(Direction::Down);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_snake.GetDirection() != Direction::Right)
		{
			m_snake.SetDirection(Direction::Left);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_snake.GetDirection() != Direction::Left)
		{
			m_snake.SetDirection(Direction::Right);
		}
	}
	void Game::Update()
	{
		m_window.Update();
		float timestep = 1.f / m_snake.GetSpeed();
		if (m_elapsed >= timestep)
		{
			m_snake.Tick();
			m_world.Update(m_snake);
			m_elapsed -= timestep;
			if (m_snake.HasLost())
			{
				m_snake.Reset();
			}
		}
	}

	void Game::Render()
	{
		m_window.BeginDraw();
		// Render here.
		m_world.Render(*m_window.GetRenderWindow());
		m_snake.Render(*m_window.GetRenderWindow());

		m_window.EndDraw();
	}

	sf::Time Game::GetElapsed() { return m_clock.getElapsedTime(); }
	void Game::RestartClock() { m_elapsed += m_clock.restart().asSeconds(); }
	Window* Game::GetWindow() { return &m_window; }
	//private:
}