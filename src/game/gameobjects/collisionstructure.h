#pragma once

#include "structure.h"

#include "../../engine/components/collider.h"

class CollisionStructure : public Structure {
   public:
    CollisionStructure();
    virtual ~CollisionStructure() = default;

    virtual void setDimensions(const sf::Vector2f& dimensions);

   protected:
    engine::Collider& collider;
};
