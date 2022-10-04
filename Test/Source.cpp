#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

void main(int argc, char** argv[]) {
	sf::RenderWindow window(sf::VideoMode(800, 600),
		"Bouncing mushroom.");
	sf::Texture mushroomTexture;
	mushroomTexture.loadFromFile("assets/Mushroom2.png");
	sf::Sprite mushroom(mushroomTexture);
	//mushroom.setScale(0.1f,0.1f);
	sf::Vector2u size = mushroomTexture.getSize();
	//size.x /= 10.f;
	//size.y /= 10.f;
	mushroom.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.04f, 0.04f);

	sf::Clock clock;

	while (window.isOpen())
	{
		

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		if ((mushroom.getPosition().x + (size.x / 2) >
			window.getSize().x && increment.x > 0) ||
			(mushroom.getPosition().x - (size.x / 2) < 0 &&
				increment.x < 0))
		{
			// Reverse the direction on X axis.
			increment.x = -increment.x;
		}
		if ((mushroom.getPosition().y + (size.y / 2) >
			window.getSize().y && increment.y > 0) ||
			(mushroom.getPosition().y - (size.y / 2) < 0 &&
				increment.y < 0))
		{
			// Reverse the direction on Y axis.
			increment.y = -increment.y;
		}

		double deltaTime = clock.restart().asSeconds();

		mushroom.setPosition(mushroom.getPosition() + (increment));
		window.clear(sf::Color(16, 16, 16, 255)); // Dark gray.
		window.draw(mushroom); // Drawing our sprite.
		window.display();
	}
}