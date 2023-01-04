#include "Moveable.h"

Moveable::Moveable(Params::Moveable params)
	: weight(params.weight), friction(Math::clamp(params.friction, 0.0f, 1.0f)), absorption(Math::clamp(params.weight, 0.0f, 1.0f))
{
	
}

Moveable::Moveable(float weight, float friction, float absorption)
	: weight(weight), friction(Math::clamp(friction, 0.0f, 1.0f)), absorption(Math::clamp(absorption, 0.0f, 1.0f))
{
}

void Moveable::ApplyForces()
{
	const int static_count = static_forces.size();
	int active_count = active_forces.size();
	const sf::Vector2f zero_vector;
	sf::Vector2f displacement(0.0f, 0.0f);

	for (int i = 0; i < active_count; i++)
	{
		const sf::Vector2f force = active_forces[i].Progress();
		if (force == zero_vector)
		{
			active_forces.erase(active_forces.begin() + i);
			i--; active_count--;
		}
		displacement += force;
	}
	for (int i = 0; i < static_count; i++)
	{
		displacement += static_forces[i].GetForce();
	}

	position += displacement;

}

void Moveable::AddStaticForce(sf::Vector2f force_dir, float force_magnitude)
{
	static_forces.push_back(ConstantForce(force_dir, force_magnitude));
}


void Moveable::AddActiveForce(sf::Vector2f force_dir, float force_magnitude)
{
	active_forces.push_back(SimpleForce(force_dir, force_magnitude, friction));
}