#pragma once

#include "gameobject.h"

#include "../components/transform.h"
#include "../components/sprite.h"

class Structure : public GameObject {
   public:
    Structure();
    virtual ~Structure() = default;

    virtual void setDimensions(const sf::Vector2f& dimensions);

   protected:
    float width;
    float height;

    Transform& transform;
    Sprite& sprite;
};