#include "Window.hpp"

namespace Snake
{
	Window::Window()
	{
		Setup("Window", sf::Vector2u(640, 480));
	}

	Window::Window(const std::string& l_title, const sf::Vector2u& l_size)
	{
		Setup(l_title, l_size);
	}

	Window::~Window()
	{
		void Destroy();
	}

	void Window::BeginDraw()
	{
		m_window.clear(sf::Color(0x3A, 0x44, 0x54));
	}
	void Window::EndDraw()
	{
		m_window.display();
	}

	void Window::Update()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_isDone = true;
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
			{
				ToggleFullScreen();
			}
		}
	}

	bool Window::IsDone()
	{
		return m_isDone;
	}
	bool Window::IsFullScreen()
	{
		return m_isFullScreen;
	}
	sf::Vector2u Window::GetWindowSize()
	{
		return m_windowSize;
	}

	void Window::ToggleFullScreen()
	{
		m_isFullScreen = !m_isFullScreen;
		Destroy();
		Create();
	}
	//private:
	void  Window::Draw(sf::Drawable& l_drawable)
	{
		m_window.draw(l_drawable);
	}

	void Window::Setup(const std::string& l_title, const sf::Vector2u& l_size)
	{
		m_windowTitle = l_title;
		m_windowSize = l_size;
		m_isFullScreen = false;
		m_isDone = false;
		Create();
	}

	void Window::Create()
	{
		auto style = (m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
		m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);

		sf::Image icon;
		icon.loadFromFile("assets/Mushroom.png");
		m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
	void Window::Destroy()
	{
		m_window.close();
	}
}