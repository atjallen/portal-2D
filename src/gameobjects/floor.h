#pragma once

#include <SFML/Graphics.hpp>

#include "gameobject.h"

#include "../components/collision.h"
#include "../components/sprite.h"
#include "../components/transform.h"

class Floor : public GameObject {
   public:
    Floor();
    virtual ~Floor() = default;

    void setDimensions(const sf::Vector2f dimensions);

   private:
    float width;
    float height;

    Transform& transform;
    Collision& collision;
    Sprite& sprite;
};
