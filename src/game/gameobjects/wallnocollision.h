#pragma once

#include "game/gameobjects/structure.h"

class WallNoCollision : public Structure {
   public:
    WallNoCollision(float width, float height, const sf::Vector2f& initialPosition);
    virtual ~WallNoCollision() = default;
};