#pragma once

#include "game/gameobjects/collisionstructure.h"

class Floor : public CollisionStructure {
   public:
    Floor(float width, float height, const sf::Vector2f& initialPosition);
    virtual ~Floor() = default;
};
