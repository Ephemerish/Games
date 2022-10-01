#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include "Score.h"

int main()
{
	//ShowWindow(GetConsoleWindow(), SW_SHOW);
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	//defination of constants
	const int screenWidth = 800;
	const int screenHeight = 600;
	sf::Vector2f paddleSize(25, 100);
	sf::Vector2f ballStartPosition(400, 300);
	sf::Vector2f leftPaddleStartPosition(25, 300);
	sf::Vector2f rightPaddleStartPosition(775, 300);
	const double pi = 3.14159f;

	//create window
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight, 32), "Pong",
		sf::Style::Titlebar | sf::Style::Close);

//	//create ball
	sf::RectangleShape ball(sf::Vector2f(7, 7));
	ball.setFillColor(sf::Color::White);
	ball.setOutlineColor(sf::Color::Black);
	ball.setOutlineThickness(3);
	ball.setOrigin(10 / 2, 10 / 2);

	// Ball Defination
	double ballSize = 10;
	double ballAngle = 0.f;
	

	// Create the left paddle
	sf::RectangleShape leftPaddle;
	leftPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
	leftPaddle.setOutlineThickness(3);
	leftPaddle.setOutlineColor(sf::Color::Black);
	leftPaddle.setFillColor(sf::Color(100, 100, 200));
	leftPaddle.setOrigin(paddleSize / 2.f);

	// Create the right paddle
	sf::RectangleShape rightPaddle;
	rightPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
	rightPaddle.setOutlineThickness(3);
	rightPaddle.setOutlineColor(sf::Color::Black);
	rightPaddle.setFillColor(sf::Color(200, 100, 100));
	rightPaddle.setOrigin(paddleSize / 2.f);
	 
	//Set Starting Posotions
	ball.setPosition(ballStartPosition);
	leftPaddle.setPosition(leftPaddleStartPosition);
	rightPaddle.setPosition(rightPaddleStartPosition);
	double speed = 400;

	// Load the text font
	sf::Font font;
	font.loadFromFile("assets/Inconsolata-Bold.ttf");

	if (!font.loadFromFile("assets/Inconsolata-Bold.ttf")) {
		std::cout << "font not loaded" << std::endl;
		return 1;
	}

	// Initialize the pause message
	sf::Text pauseMessage;
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(40);
	pauseMessage.setPosition(100.f, 150.f);
	pauseMessage.setFillColor(sf::Color::White);
	pauseMessage.setString("\t\t SFML Pong!\nPress space to start the game");

	sf::Clock clock;
	Pong::Score score;

	double max = 0;
	sf::Event event;
	bool isPlaying = false;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			//close if x is clicked or Escape is pressed
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				window.close();
				break;
			}

			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
			{
				if (!isPlaying)
				{
					// (re)start the game
					isPlaying = true;
					clock.restart();
					speed = 400;

					// Reset the position of the paddles and ball
					ball.setPosition(ballStartPosition);
					leftPaddle.setPosition(leftPaddleStartPosition);
					rightPaddle.setPosition(rightPaddleStartPosition);
				}
			}
		}

		if (isPlaying)
		{
			const double paddleSpeed = 400.f;
			double deltaTime = clock.restart().asSeconds();
			// Move the player 1's paddle
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
				(leftPaddle.getPosition().y - paddleSize.y / 2 > 5))
			{
				leftPaddle.move(0.f, -paddleSpeed * deltaTime);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
				(leftPaddle.getPosition().y + paddleSize.y / 2 < screenHeight - 5))
			{
				leftPaddle.move(0.f, paddleSpeed * deltaTime);
			}

			// Move the player 2's paddle
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
				(rightPaddle.getPosition().y - paddleSize.y / 2 > 5))
			{
				rightPaddle.move(0.f, -paddleSpeed * deltaTime);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
				(rightPaddle.getPosition().y + paddleSize.y / 2 < screenHeight - 5))
			{
				rightPaddle.move(0.f, paddleSpeed * deltaTime);
			}

			// Check the collisions between the walls
			if (ball.getPosition().x - ballSize < 0.f)
			{
				score.addPointsRight();
				pauseMessage.setString(score.getStanding());
				isPlaying = false;
				ballAngle = 0.f;
			}
			if (ball.getPosition().x + ballSize > screenWidth)
			{
				score.addPointsLeft();
				pauseMessage.setString(score.getStanding());
				//pauseMessage.setString("\t\tLeft won!\nPress space to restart or\n\t  escape to exit");
				isPlaying = false;
				ballAngle = 3.14f;
			}
			if (ball.getPosition().y - ballSize < 0.f)
			{
				ballAngle = -ballAngle;
				ball.setPosition(ball.getPosition().x, ballSize + 0.1f);
			}
			if (ball.getPosition().y + ballSize > screenHeight)
			{
				ballAngle = -ballAngle;
				ball.setPosition(ball.getPosition().x, screenHeight - ballSize - 0.1f);
			}

			// Check the collisions between the ball and the paddles
				// Left Paddle
			if (ball.getPosition().x - ballSize < leftPaddle.getPosition().x + paddleSize.x / 2 &&
				ball.getPosition().x - ballSize > leftPaddle.getPosition().x &&
				ball.getPosition().y + ballSize >= leftPaddle.getPosition().y - paddleSize.y / 2 &&
				ball.getPosition().y - ballSize <= leftPaddle.getPosition().y + paddleSize.y / 2)
			{
				if (ball.getPosition().y > leftPaddle.getPosition().y)
					ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
				else
					ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

				ball.setPosition(leftPaddle.getPosition().x + ballSize + paddleSize.x / 2 + 0.1f, ball.getPosition().y);
				//Speed ramp up
				speed += 10;
			}

			// Right Paddle
			if (ball.getPosition().x + ballSize > rightPaddle.getPosition().x - paddleSize.x / 2 &&
				ball.getPosition().x + ballSize < rightPaddle.getPosition().x &&
				ball.getPosition().y + ballSize >= rightPaddle.getPosition().y - paddleSize.y / 2 &&
				ball.getPosition().y - ballSize <= rightPaddle.getPosition().y + paddleSize.y / 2)
			{
				if (ball.getPosition().y > leftPaddle.getPosition().y)
					ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
				else
					ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

				ball.setPosition(rightPaddle.getPosition().x - ballSize - paddleSize.x / 2 - 0.1f, ball.getPosition().y);
				//Speed ramp up
				speed += 10;
			}

			// Move the ball
			double factor = speed * deltaTime;
			ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);
			//ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * 0);

			//Debug
			std::cout << "Ball angle = " << ballAngle << std::endl;
			std::cout << rightPaddle.getPosition().x << ", " << rightPaddle.getPosition().y << std::endl;
			std::cout << ball.getPosition().x << ", " << ball.getPosition().y << std::endl;
			std::cout << "==============================================" << std::endl;
			if (ball.getPosition().x > max)
				max = ball.getPosition().x;
		}

		//reset Animation
		if (!isPlaying)
		{
			//sf::Vector2f ballResetDistance = ball.getPosition() - 
		}

		
		

		if(!isPlaying)
		{
			//window
			window.clear(sf::Color(0xff, 0xC3, 0x0F));
			// Draw the pause message
			window.draw(pauseMessage);
		}
		else if (isPlaying)
		{
			//Window
			window.clear(sf::Color(0xff, 0xC3, 0x0F));
			// Draw the paddles and the ball
			window.draw(leftPaddle);
			window.draw(rightPaddle);
			window.draw(ball);
			window.draw(score.standing);
		}
		

		window.display();
	}

	std::cout << max;
	return EXIT_SUCCESS;
}