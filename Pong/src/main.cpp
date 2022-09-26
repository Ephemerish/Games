#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

#define pi 3.14

int main()
{
	//ShowWindow(GetConsoleWindow(), SW_SHOW);
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	//defination of constants
	const int screenWidth = 800;
	const int screenHeight = 600;
	double ballPosition[2] = {400, 300};
	sf::Vector2f paddleSize(25, 100);

	//create window
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight, 32), "Test",
		sf::Style::Titlebar | sf::Style::Close);

	//create ball
	sf::RectangleShape ball(sf::Vector2f(7, 7));
	ball.setFillColor(sf::Color::White);
	ball.setOutlineColor(sf::Color::Black);
	ball.setOutlineThickness(3);
	float ballAngle = 0.f;

	// Create the left paddle
	sf::RectangleShape leftPaddle;
	leftPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
	leftPaddle.setOutlineThickness(3);
	leftPaddle.setOutlineColor(sf::Color::Black);
	leftPaddle.setFillColor(sf::Color(100, 100, 200));
	//leftPaddle.setOrigin(paddleSize / 2.f);

	// Create the right paddle
	sf::RectangleShape rightPaddle;
	rightPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
	rightPaddle.setOutlineThickness(3);
	rightPaddle.setOutlineColor(sf::Color::Black);
	rightPaddle.setFillColor(sf::Color(200, 100, 100));
	//rightPaddle.setOrigin(paddleSize / 2.f);

	ball.setPosition(ballPosition[0], ballPosition[1]);
	leftPaddle.setPosition(0, 100);
	rightPaddle.setPosition(775, 500);
	double speed = 400;
	sf::Clock clock;

	double max = 0;
	sf::Event event;
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
		}


		const float paddleSpeed = 400.f;
		float deltaTime = clock.restart().asSeconds();
		// Move the player 1's paddle
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			(leftPaddle.getPosition().y > 5.f))
		{
			leftPaddle.move(0.f, -paddleSpeed * deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
			(leftPaddle.getPosition().y + paddleSize.y < screenHeight))
		{
			leftPaddle.move(0.f, paddleSpeed * deltaTime);
		}

		// Move the player 2's paddle
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
			(rightPaddle.getPosition().y > 5.f))
		{
			rightPaddle.move(0.f, -paddleSpeed * deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
			(rightPaddle.getPosition().y + paddleSize.y < screenHeight))
		{
			rightPaddle.move(0.f, paddleSpeed * deltaTime);
		}

		// Check the collisions between the walls
		if (ball.getPosition().x - 10 < 0.f)
		{
			speed = -speed;
			//pauseMessage.setString("You lost!\nPress space to restart or\nescape to exit");
		}
		if (ball.getPosition().x + 10 > screenWidth)
		{
			speed = -speed;
			//pauseMessage.setString("You won!\nPress space to restart or\nescape to exit");
		}
		if (ball.getPosition().y - 10 < 0.f)
		{
			ballAngle = -ballAngle;
			ball.setPosition(ball.getPosition().x, 10 + 0.1f);
		}
		if (ball.getPosition().y + 10 > screenHeight)
		{
			ballAngle = -ballAngle;
			ball.setPosition(ball.getPosition().x, screenHeight - 10 - 0.1f);
		}

		// Check the collisions between the ball and the paddles
			// Left Paddle
		if (ball.getPosition().x + 7< leftPaddle.getPosition().x + paddleSize.x &&
			ball.getPosition().x > leftPaddle.getPosition().x &&
			ball.getPosition().y >= leftPaddle.getPosition().y &&
			ball.getPosition().y + 7<= leftPaddle.getPosition().y + paddleSize.y)
		{
			if (ball.getPosition().y > leftPaddle.getPosition().y)
				ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
			else
				ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

			speed = -speed;
		}

		// Right Paddle
		if (ball.getPosition().x - 7 > rightPaddle.getPosition().x - paddleSize.x &&
			ball.getPosition().x < rightPaddle.getPosition().x &&
			ball.getPosition().y >= rightPaddle.getPosition().y &&
			ball.getPosition().y - 7 <= rightPaddle.getPosition().y + paddleSize.y)
		{
			if (ball.getPosition().y > leftPaddle.getPosition().y)
				ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
			else
				ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

			speed = -speed;
		}

		// Move the ball
		float factor = speed * deltaTime;
		ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);

		//debug
		std::cout << "Ball angle = " << ballAngle << std::endl;
		std::cout << rightPaddle.getPosition().x << ", " << rightPaddle.getPosition().y << std::endl;
		std::cout << ball.getPosition().x << ", " << ball.getPosition().y << std::endl;
		std::cout << "==============================================" << std::endl;
		if (ball.getPosition().x > max)
			max = ball.getPosition().x;

		window.clear(sf::Color(0xff, 0xbf, 0x65));
		window.draw(ball);
		window.draw(leftPaddle);
		window.draw(rightPaddle);
		window.display();
	}

	std::cout << max;
	return EXIT_SUCCESS;
}