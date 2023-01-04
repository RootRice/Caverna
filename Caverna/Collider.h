#pragma once
#include <SFML/Graphics.hpp>
class Collider
{
public:
	virtual Collider& GetType() = 0;
protected:
	Collider();

	float bounds_radius;


};

