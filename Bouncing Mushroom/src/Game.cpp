#include "Game.hpp"

namespace Daklit
{
	//public:
	Game::Game() : m_window("Bouncing Mushroom", sf::Vector2u(800, 600))
	{
		m_mushroomTexture.loadFromFile("assets/Mushroom.png");
		m_mushroom.setTexture(m_mushroomTexture);
		m_increment = sf::Vector2i(200, 200);
	}
	Game::~Game() {}

	void Game::HandleInput()
	{
	}
	void Game::Update()
	{
		m_window.Update();
		MoveMushroom();
	}
	void Game::Render()
	{
		//clear screen
		m_window.BeginDraw();
		m_window.Draw(m_mushroom);
		// Display.
		m_window.EndDraw();
	}
	Window* Game::GetWindow()
	{
		return&m_window;
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
	void Game::MoveMushroom()
	{
		sf::Vector2u l_windowSize = m_window.GetWindowSize();
		sf::Vector2u l_textureSize = m_mushroomTexture.getSize();

		if ((m_mushroom.getPosition().x > l_windowSize.x - l_textureSize.x && m_increment.x > 0) ||
			(m_mushroom.getPosition().x < 0 && m_increment.x < 0))
		{
			m_increment.x = -m_increment.x;
		}

		if ((m_mushroom.getPosition().y > l_windowSize.y - l_textureSize.x && m_increment.y > 0) ||
			(m_mushroom.getPosition().y < 0 && m_increment.y < 0))
		{
			m_increment.y = -m_increment.y;
		}

		float fElapsed = m_elapsed.asSeconds();
		m_mushroom.setPosition(
			m_mushroom.getPosition().x + (m_increment.x * fElapsed),
			m_mushroom.getPosition().y + (m_increment.y * fElapsed)
		);
	}
}