#include "SimpleForce.h"

sf::Vector2f SimpleForce::Progress()
{
	constexpr float zero_threshold = 0.01f;
	magnitude *= damp_rate;
	magnitude *= magnitude > zero_threshold; //set magnitude to 0 if magnitude is less than threshold
	return dir*magnitude;
}
