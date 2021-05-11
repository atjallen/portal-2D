#pragma once

#include "gameobject.h"

#include "../components/collision.h"
#include "../components/physics.h"
#include "../components/sprite.h"
#include "../components/transform.h"

class Player : public GameObject {
   public:
    Player();
    virtual ~Player() = default;

    virtual void fixedUpdate(const sf::Time& frameTime);

   private:
    float acceleration;

    Transform& transform;
    Physics& physics;
    Collision& collision;
    Sprite& sprite;
};
