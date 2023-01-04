#include "ConstantForce.h"

ConstantForce::ConstantForce(sf::Vector2f dir, float magnitude)
	: magnitude(magnitude)
{
	if (magnitude != 0)
	{
		this->dir = Math::v_normalise(dir);
	}
	else
	{
		this->dir = sf::Vector2f(0.0f, 0.0f);
	}

}

sf::Vector2f ConstantForce::GetForce()
{
	return dir*magnitude;
}

void ConstantForce::SetForce(sf::Vector2f _dir, float _magnitude)
{
	if (Math::v_magnitude(_dir) != 0)
		dir = Math::v_normalise(_dir);
	else
		dir = sf::Vector2f();
	magnitude = _magnitude;

}
