#pragma once

#include "game/gameobjects/collisionstructure.h"

class Ceiling : public CollisionStructure {
   public:
    Ceiling();
    virtual ~Ceiling() = default;
};
