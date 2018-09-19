#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
//#include <graphics.h>

std::vector<sf::RectangleShape> rects;
std::vector<sf::RectangleShape> lines;

int count = 0;

void put_pixel(sf::Vector2i pos)
{
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

void change_color(sf::Vector2i pos, sf::Mouse::Button button, sf::RenderWindow &window)
{
	for (auto& r : rects)
	{
		if (isPixelClicked(r, button, window))
		{
			r.setFillColor(sf::Color(0, 255, 0));
		}
	}
}

void change_color(sf::RectangleShape clickedPixel)
{
	clickedPixel.setFillColor(sf::Color(0, 255, 0));
}

void drawLine(sf::RenderWindow &window, float x0, float y0, float x1, float y1)
{
	float dx, dy, error, x, y;
	dx = x1 - x0;
	dy = y1 - y0;

	x = x0;
	y = y0;

	error = 2 * dy - dx;

	while (x < x1)
	{
		if (error >= 0)
		{
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(x0, y0)),
				sf::Vertex(sf::Vector2f(x1, y1))
			};
			y = y + 1;
			error = error + 2 * dy - 2 * dx;
			window.draw(line, 2, sf::Lines);
		}
		else
		{
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(x0, y0)),
				sf::Vertex(sf::Vector2f(x1, y1))
			};
			error = error + 2 * dy;
			window.draw(line, 2, sf::Lines);
		}
		x = x + 1;
	}
}

int main() {
	sf::RenderWindow window({ 1024, 769 }, "Hello World");

	while (window.isOpen()) {
		sf::Event event;

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
					change_color(mousePos, event.mouseButton.button, window);
				}
			}
		}
		
		window.clear();

		drawLine(window, 100, 100, 400, 400);

		for (auto& r : rects)
		{
			window.draw(r);
		}
		window.display();
	}
}

//for next week, get all steps till 6 done