#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Snake
{
	class Textbox
	{
	public:
		Textbox();
		Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);
		~Textbox();

		void Setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);

		void Add(std::string l_message);
		void Clear();

		void Render(sf::RenderWindow& l_wind);
	private:
		std::vector<std::string> m_messages;
		int m_numberVisible;

		sf::RectangleShape m_backdrop;
		sf::Font m_font;
		sf::Text m_content;
	};
}
