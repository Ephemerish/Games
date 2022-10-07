#include "Window.hpp"

namespace Daklit
{
	Window::Window()
	{
		Setup("Window", sf::Vector2u(800, 600));
	}

	Window::Window(const std::string& l_title, const sf::Vector2u& l_size)
	{
		Setup(l_title, l_size);
	}

	Window::~Window()
	{
		void Destroy();
	}

	void Window::BeginDraw(sf::Color color)
	{
		m_window.clear(color);
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
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				m_isDone = true;
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
			{
				ToggleFullScreen();
			}

			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
			{
				m_isPlaying = true;
			}
		}
	}

	bool Window::IsDone()
	{
		return m_isDone;
	}
	void Window::Done()
	{
		m_isDone = true;
	}
	bool Window::IsPlaying()
	{
		return m_isPlaying;
	}
	void Window::Playing()
	{
		m_isPlaying = true;
	}
	void Window::notPlaying()
	{
		m_isPlaying = false;
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
		m_isPlaying = false;
		Create();
	}

	void Window::Create()
	{
		auto style = (m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
		m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
	}
	void Window::Destroy()
	{
		m_window.close();
	}
}