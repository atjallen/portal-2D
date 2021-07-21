#pragma once

#include "../../engine/gameobject.h"

#include "portalgun.h"

#include "../../engine/components/collider.h"
#include "../../engine/components/physics.h"
#include "../../engine/components/sprite.h"
#include "../../engine/components/transform.h"

class Player : public engine::GameObject {
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

    engine::Transform& transform;
    engine::Physics& physics;
    engine::Collider& collider;
    engine::Sprite& sprite;
};
