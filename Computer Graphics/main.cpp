#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

std::vector<sf::RectangleShape> rects;

void put_pixel(sf::Vector2i pos) {
	sf::RectangleShape pixel{ {10, 10} };
	pixel.setPosition(sf::Vector2f(pos));
	pixel.setFillColor(sf::Color(255, 0, 0));
	rects.push_back(pixel);
}

bool isPixelClicked(sf::RectangleShape pix, sf::Mouse::Button button, sf::RenderWindow &window)
{
	if (sf::Mouse::isButtonPressed)
	{
		sf::IntRect pixelClick(pix.getPosition().x, pix.getPosition().y, pix.getGlobalBounds().width,
			pix.getGlobalBounds().height);

		if (pixelClick.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}
	}
	return false;
}

int main() {
	sf::RenderWindow window({ 1024, 769 }, "Hello World");

	window.setFramerateLimit(30);
	while (window.isOpen()) {
		sf::Event event;

		sf::Vector2i mouseDownPos;
		while (window.pollEvent(event)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vertex line[2];

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					put_pixel(mousePos);
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					//std::cout << mousePos.x << ", " << mousePos.y << std::endl;
					sf::RectangleShape foundRect;
					for (auto& r : rects)
					{
						bool yes = isPixelClicked(r, event.mouseButton.button, window);
						if (yes)
						{
							r.setFillColor(sf::Color(0, 255, 0));
						}
					}
				}
			}
			window.clear();
		}

		for (auto& r : rects)
		{
			window.draw(r);
		}
		window.display();
	}
}


