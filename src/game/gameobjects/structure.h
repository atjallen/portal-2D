#pragma once

#include "engine/gameobject.h"

#include "engine/components/sprite.h"
#include "engine/components/transform.h"

class Structure : public engine::GameObject {
   public:
    Structure(float width, float height, const sf::Vector2f& initialPosition);
    virtual ~Structure() = default;

   protected:
    float width;
    float height;

    engine::Transform& transform;
    engine::Sprite& sprite;
};