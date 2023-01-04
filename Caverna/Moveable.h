#pragma once
#include "Utils.cpp"
#include "SimpleForce.h"
#include "ConstantForce.h"
#include <algorithm>



class Moveable
{
public:
	Moveable(Params::Moveable params);
	Moveable(float weight, float friction, float absorption);

	void ApplyForces();

	void AddActiveForce(sf::Vector2f force_dir, float force_magnitude);
	void AddStaticForce(sf::Vector2f force_dir, float force_magnitude);

private:
	float weight;
	float friction;
	float absorption;

	std::vector<SimpleForce> active_forces;
	
protected:
	sf::Vector2f position;
	std::vector<ConstantForce> static_forces;
};                                                                                                                                                                                                                                                                                                                                                                                                                                