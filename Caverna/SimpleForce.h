#pragma once
#include "SFML/Graphics.hpp"
#include "Utils.cpp"
class SimpleForce
{
public:
	SimpleForce(sf::Vector2f dir, float magnitude, float damp_rate) : dir(Math::v_normalise(dir)), magnitude(magnitude), damp_rate(damp_rate) {};
	sf::Vector2f Progress();
private:
	sf::Vector2f dir;
	float magnitude;
	float damp_rate;
};

