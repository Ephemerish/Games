#pragma once
#include <SFML/Graphics.hpp>

namespace Daklit
{
	class Window
	{
	public:
		Window();
		Window(const std::string& l_title, const sf::Vector2u& l_size);
		~Window();

		void BeginDraw();
		void EndDraw();

		void Update();

		bool IsDone();
		bool IsFullScreen();

		sf::RenderWindow* GetRenderWindow();
		sf::Vector2u GetWindowSize();

		void ToggleFullScreen();

		void Draw(sf::Drawable& l_drawable);
	private:
		bool m_isDone;
		bool m_isFullScreen;

		void Setup(const std::string& l_title, const sf::Vector2u& l_size);
		void Create();
		void Destroy();

		sf::RenderWindow m_window;
		sf::Vector2u m_windowSize;
		std::string m_windowTitle;
	};
}