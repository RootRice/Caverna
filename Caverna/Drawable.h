#pragma once
#include <SFML/Graphics.hpp>
class Drawable
{
public:
	virtual void Draw(sf::RenderWindow& window) = 0;
};

