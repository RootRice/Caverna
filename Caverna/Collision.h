#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
class Collision
{
public:
	static void AddCollidable(Collider& collider);
	static void RemoveCollidable(Collider& collider);
	static void TestCollisions(sf::RenderWindow& _window);
private:
	static std::vector<std::reference_wrapper<Collider>> colliders;

	static void KD(float mean, std::vector<std::reference_wrapper<Collider>>& cols, int depth, sf::RenderWindow& _window);
	static bool Compare(std::vector<std::reference_wrapper<Collider>> a, std::vector<std::reference_wrapper<Collider>> b);

};

