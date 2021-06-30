#pragma once

#include "collisionstructure.h"

class Floor : public CollisionStructure {
   public:
    Floor();
    virtual ~Floor() = default;
};
