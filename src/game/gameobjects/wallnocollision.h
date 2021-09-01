#pragma once

#include "game/gameobjects/structure.h"

class WallNoCollision : public Structure {
   public:
    WallNoCollision();
    virtual ~WallNoCollision() = default;
};