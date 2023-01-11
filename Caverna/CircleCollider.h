#pragma once
#include "Collider.h"
class CircleCollider :
    public Collider
{
public:
    Collider& GetType() override;
    CircleCollider(float bounds_radius, const sf::Vector2f& position) : Collider(bounds_radius, position) {};
    sf::Vector2f GetPos() { return position; };
};

