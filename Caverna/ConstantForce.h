#pragma once
#include <SFML/Graphics.hpp>
#include "Utils.cpp"
class ConstantForce
{
public:
	ConstantForce(sf::Vector2f dir, float magnitude);

	sf::Vector2f GetForce();
	void SetForce(sf::Vector2f dir, float magnitude);
private:
	sf::Vector2f dir;
	float magnitude;
};

