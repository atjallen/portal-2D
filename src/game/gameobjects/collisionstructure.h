#pragma once

#include "structure.h"

#include "engine/components/collider.h"

class CollisionStructure : public Structure {
   public:
    CollisionStructure(float width, float height, const sf::Vector2f& initialPosition);
    virtual ~CollisionStructure() = default;

   protected:
    engine::Collider& collider;
};
