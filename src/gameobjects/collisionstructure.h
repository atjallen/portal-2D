#pragma once

#include "structure.h"

#include "../components/collision.h"

class CollisionStructure : public Structure {
   public:
    CollisionStructure();
    virtual ~CollisionStructure() = default;

    virtual void setDimensions(const sf::Vector2f& dimensions);

   protected:
    Collision& collision;
};
