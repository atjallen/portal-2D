#pragma once

#include "game/gameobjects/collisionstructure.h"

class Floor : public CollisionStructure {
   public:
    Floor();
    virtual ~Floor() = default;
};
