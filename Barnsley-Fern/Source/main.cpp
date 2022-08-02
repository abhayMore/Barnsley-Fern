#include <SFML/Graphics.hpp>
#include<iostream>
#include<cmath>
#include <cstdlib>
#include <ctime>


int mapValue(double value, double low1, double high1, int low2, int high2)
{
	return static_cast<int>(low2 + static_cast<float>((value - low1) * (high2 - low2)) / (high1 - low1));
}

int ReturnIntRandom(int lower, int upper)
{
	return (rand() % (upper - lower + 1)) + lower;
}

void getPoints(sf::Vector2f& prevPoint)
{
	sf::Vector2f newPoint;
	float probability = ReturnIntRandom(0, 100);
	if (probability < 1)
	{
		newPoint.x =  0;
		newPoint.y =  0.16 * prevPoint.y;
	}
	else if (probability < 86)
	{
		newPoint.x =  0.85 * prevPoint.x + 0.04 * prevPoint.y;
		newPoint.y = -0.04 * prevPoint.x + 0.85 * prevPoint.y + 1.6;
	}
	else if (probability < 93)
	{
		newPoint.x =  0.20 * prevPoint.x -  0.26 * prevPoint.y;
		newPoint.y =  0.23 * prevPoint.x +  0.22 * prevPoint.y + 1.6;
	}
	else
	{
		newPoint.x = -0.15 * prevPoint.x + 0.28 * prevPoint.y;
		newPoint.y =  0.26 * prevPoint.x + 0.24 * prevPoint.y + 0.44;
	}
	prevPoint = newPoint;
}

int main()
{
	srand(time(0));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(950, 950), "Barnsley-Fern", sf::Style::Titlebar | sf::Style::Close, settings);
	//window.setFramerateLimit(60);

	sf::RenderTexture canvas;
	canvas.create(window.getSize().x, window.getSize().y);
	sf::Sprite sprite;
	sprite.setTexture(canvas.getTexture(), true);
	
	sf::CircleShape shape(0.3f);
	shape.setFillColor(sf::Color::Green);
	sf::Vector2f prevPoint(0.0f, 0.0f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}
		getPoints(prevPoint);
		auto xp = mapValue(prevPoint.x, -2.1820, 2.6558, 100, 900);
		auto yp = mapValue(prevPoint.y, 0, 9.9983, 900, 100);
		shape.setPosition(sf::Vector2f(xp, yp));	
		canvas.draw(shape);
		canvas.display();
		
		window.clear();
		window.draw(sprite);
		window.display();
	}
	return 0;
}