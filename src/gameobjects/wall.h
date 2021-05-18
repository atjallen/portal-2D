#pragma once

#include "collisionstructure.h"

class Wall : public CollisionStructure {
   public:
    Wall();
    virtual ~Wall() = default;
};