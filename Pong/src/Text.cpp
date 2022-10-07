#include "Text.hpp"

namespace Daklit
{
	Text::Text()
	{
		void Setup();
	}
	Text::~Text()
	{
	}

	void Text::Setup()
	{
		int LoadFont();
		void Debug();
		void Score();
		void PauseMessage();
	}
	int Text::LoadFont()
	{
		m_font.loadFromFile("assets/Inconsolata-Bold.ttf");

		if (!m_font.loadFromFile("assets/Inconsolata-Bold.ttf")) {
			std::cout << "font not loaded" << std::endl;
			return 1;
		}
		else
			return 0;
	}

	void Text::DebugMessage()
	{
	}
	void Text::ScoreMessage()
	{
	}
	void Text::PauseMessage()
	{
		m_pauseMessage.setFont(m_font);
		m_pauseMessage.setCharacterSize(40);
		m_pauseMessage.setPosition(100.f, 150.f);
		m_pauseMessage.setFillColor(sf::Color::White);
		m_pauseMessage.setString("\t\t SFML Pong!\nPress space to start the game");
	}

	sf::Text* Text::GetPauseMessage()
	{
		return&m_pauseMessage;
	}
}