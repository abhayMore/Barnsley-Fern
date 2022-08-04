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

sf::Color getColor(int y, int height)
{
	sf::Color shapeColor;
	if (y < height / 6)
	{
		shapeColor = sf::Color(255, mapValue(y, 0,  height / 6, 0, 255), 0);
	}
	else if (y < height / 3)
	{
		shapeColor = sf::Color(mapValue(y, height / 6, height / 3, 255, 0), 255, 0 );
	}
	else if (y < height / 2)
	{
		shapeColor = sf::Color(0, 255, mapValue(y, height / 3, height / 2, 0, 255));
	}
	else if (y < height / 1.5)
	{
		shapeColor = sf::Color(0, mapValue(y, height / 2, height / 1.5, 255, 0), 255);
	}
	else if (y < 4 * (height / 3))
	{
		shapeColor = sf::Color(mapValue(y, height / 1.5, (height / 3)*4, 0, 255), 0, 255 );
	}
	else
	{
		shapeColor = sf::Color(255, 0, mapValue(y, height / 1.5, (height / 3)*4, 0, 255));
	}
	return shapeColor;
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
	shape.setFillColor(sf::Color::Green);   //Default Color

	sf::Vector2f prevPoint(0.0f, 0.0f);

	int tempHigh = 900;
	int tempLow = 50;
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
		auto xp = mapValue(prevPoint.x, -2.1820, 2.6558, tempLow, tempHigh);
		auto yp = mapValue(prevPoint.y, 0, 9.9983, tempHigh, tempLow);

		//COLOR CALCULATION
		shape.setFillColor(getColor(yp, tempHigh));

		shape.setPosition(sf::Vector2f(xp, yp));
		canvas.draw(shape);
		canvas.display();

		window.clear();
		window.draw(sprite);
		window.display();
	}
	return 0;
}