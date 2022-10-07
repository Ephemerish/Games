#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Daklit
{
	class Window
	{
	public:
		Window();
		Window(const std::string& l_title, const sf::Vector2u& l_size);
		~Window();

		void BeginDraw(sf::Color color);
		void EndDraw();

		void Update();

		bool IsDone();
		void Done();
		bool IsPlaying();
		void Playing();
		void notPlaying();
		bool IsFullScreen();
		sf::Vector2u GetWindowSize();

		void ToggleFullScreen();

		void Draw(sf::Drawable& l_drawable);
	private:
		bool m_isDone;
		bool m_isPlaying;
		bool m_isFullScreen;

		void Setup(const std::string& l_title, const sf::Vector2u& l_size);
		void Create();
		void Destroy();

		sf::RenderWindow m_window;
		sf::Vector2u m_windowSize;
		std::string m_windowTitle;
	};
}