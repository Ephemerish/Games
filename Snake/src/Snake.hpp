#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "Textbox.hpp"

namespace Snake
{
	struct SnakeSegment
	{
		SnakeSegment(int x, int y) : position(x, y) {}
		sf::Vector2i position;
	};

	enum class Direction
	{
		None, Up, Down, Left, Right
	};

	class Snake
	{
	public:
		Snake(int l_blockSize, Textbox* l_textbox);
		~Snake();

		void SetDirection(Direction l_direction);
		Direction GetDirection();
		int GetSpeed();
		sf::Vector2i GetPosition();
		int GetLives();
		int GetScore();
		void IncreaseScore();
		bool HasLost();

		void Lose();
		void ToggleLost();

		void Extend();
		void Reset();

		Direction GetPhysicalDirection();

		void Move();
		void Tick();
		void Cut(int l_segments);
		void Render(sf::RenderWindow& l_window);
	private:
		void CheckCollision();

		std::deque<SnakeSegment> m_snakeBody;
		int m_size;
		Direction m_dir;
		int m_speed;
		int m_lives;
		int m_score;
		bool m_lost;
		sf::RectangleShape m_bodyRect;

		Textbox* m_textbox;
	};
}