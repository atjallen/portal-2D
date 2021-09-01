#pragma once

#include "game/gameobjects/collisionstructure.h"

class Wall : public CollisionStructure {
   public:
    Wall();
    virtual ~Wall() = default;
};