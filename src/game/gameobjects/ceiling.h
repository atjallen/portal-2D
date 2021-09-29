#pragma once

#include "game/gameobjects/collisionstructure.h"

class Ceiling : public CollisionStructure {
   public:
    Ceiling(float width, float height, const sf::Vector2f& initialPosition);
    virtual ~Ceiling() = default;
};
