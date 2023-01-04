#pragma once
#include "Collider.h"
class CircleCollider :
    public Collider
{
public:
    Collider& GetType() override;
};

