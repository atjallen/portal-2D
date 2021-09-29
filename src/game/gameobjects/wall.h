#pragma once

#include "game/gameobjects/collisionstructure.h"

class Wall : public CollisionStructure {
   public:
    Wall(float width, float height, const sf::Vector2f& initialPosition);
    virtual ~Wall() = default;
};