#pragma once
#include "Window.hpp"

namespace Daklit
{
	class Text
	{
	public:
		Text();
		~Text();
		void Setup();
		int LoadFont();
		void DebugMessage();
		void ScoreMessage();
		void PauseMessage();

		sf::Text* GetPauseMessage();
		sf::Text m_pauseMessage;
	private:
		sf::Font m_font;
		sf::Text m_debug;
		sf::Text m_score;
	};
}