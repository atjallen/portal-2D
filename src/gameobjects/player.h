#pragma once

#include "gameobject.h"

#include "portalgun.h"

#include "../components/collision.h"
#include "../components/physics.h"
#include "../components/sprite.h"
#include "../components/transform.h"

class Player : public GameObject {
   public:
    Player();
    virtual ~Player() = default;

    virtual void update(const sf::Time& frameTime);
    virtual void fixedUpdate(const sf::Time& frameTime);

    void setPortalGun(PortalGun& portalGun);

   private:
    float runAcceleration;
    float jumpPower;
    float floorDrag;
    float maxRunSpeed;

    PortalGun* portalGun;

    Transform& transform;
    Physics& physics;
    Collision& collision;
    Sprite& sprite;
};
