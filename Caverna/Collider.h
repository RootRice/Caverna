#pragma once
#include <SFML/Graphics.hpp>
class Collider
{
public:
	virtual Collider& GetType() = 0;
	float GetRadius();
	const sf::Vector2f& GetPosition();
	void DebugCollider(sf::RenderWindow& window);
protected:
	Collider(float bounds_radius, const sf::Vector2f& position);

	float bounds_radius;
	const sf::Vector2f& position;


};

