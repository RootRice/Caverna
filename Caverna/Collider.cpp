#include "Collider.h"
#include "Collision.h"

float Collider::GetRadius()
{
	return bounds_radius;
}

const sf::Vector2f& Collider::GetPosition()
{
	return position;
}

void Collider::DebugCollider(sf::RenderWindow& window)
{
	sf::CircleShape c(bounds_radius, 30);
	c.setFillColor(sf::Color::Green);
	c.setOrigin(sf::Vector2f(bounds_radius, bounds_radius));
	c.setPosition(position);
	window.draw(c);
}

Collider::Collider(float bounds_radius, const sf::Vector2f& position) : bounds_radius(bounds_radius), position(position)
{ 
	Collision::AddCollidable(*this); 
}
