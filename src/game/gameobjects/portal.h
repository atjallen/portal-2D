#pragma once

#include "../../engine/gameobject.h"

#include "../../engine/components/collider.h"
#include "../../engine/components/sprite.h"
#include "../../engine/components/transform.h"

class Portal : public engine::GameObject {
   public:
    Portal();
    virtual ~Portal() = default;

    void setColor(const sf::Color& color);

   private:
    engine::Transform& transform;
    engine::Sprite& sprite;
    engine::Collider& collider;
};
