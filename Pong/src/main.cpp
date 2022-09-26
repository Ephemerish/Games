#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <windows.h>

int main()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	//defination of constants
	const int screenWidth = 800;
	const int screenHeight = 600;
	sf::Vector2f paddleSize(25, 100);
	sf::Vector2f ballStartPosition(400, 300);
	sf::Vector2f leftPaddleStartPosition(25, 300);
	sf::Vector2f rightPaddleStartPosition(775, 300);
	const float pi = 3.14159f;

	//create window
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight, 32), "Pong",
		sf::Style::Titlebar | sf::Style::Close);

	//create ball
	sf::RectangleShape ball(sf::Vector2f(7, 7));
	ball.setFillColor(sf::Color::White);
	ball.setOutlineColor(sf::Color::Black);
	ball.setOutlineThickness(3);
	ball.setOrigin(10 / 2, 10 / 2);

	// Ball Defination
	float ballSize = 10;
	float ballAngle = 0.f;
	

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

	ball.setPosition(ballStartPosition);
	leftPaddle.setPosition(leftPaddleStartPosition);
	rightPaddle.setPosition(rightPaddleStartPosition);
	double speed = 400;
	sf::Clock clock;

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

					// Reset the ball angle
					
					ballAngle = 0;
				}
			}
		}

		if (isPlaying)
		{
			const float paddleSpeed = 400.f;
			float deltaTime = clock.restart().asSeconds();
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
				//speed = -speed;
				//pauseMessage.setString("You lost!\nPress space to restart or\nescape to exit");
				isPlaying = false;
			}
			if (ball.getPosition().x + ballSize > screenWidth)
			{
				//speed = -speed;
				//pauseMessage.setString("You won!\nPress space to restart or\nescape to exit");
				isPlaying = false;
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
				speed += 10;
				//speed = -speed;
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
				speed += 10;
				//speed = -speed;
			}

			// Move the ball
			float factor = speed * deltaTime;
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

		//Window
		window.clear(sf::Color(0xff, 0xbf, 0x65));
		window.draw(ball);
		window.draw(leftPaddle);
		window.draw(rightPaddle);
		window.display();
	}

	std::cout << max;
	return EXIT_SUCCESS;
}