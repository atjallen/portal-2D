#pragma once

#include "../../engine/gameobject.h"

#include "../../engine/components/sprite.h"
#include "../../engine/components/transform.h"

class Structure : public engine::GameObject {
   public:
    Structure();
    Structure(const sf::Vector2f& initialPosition, const sf::Vector2f& dimensions);
    virtual ~Structure() = default;

    virtual void setDimensions(const sf::Vector2f& dimensions);

   protected:
    float width;
    float height;

    engine::Transform& transform;
    engine::Sprite& sprite;
};