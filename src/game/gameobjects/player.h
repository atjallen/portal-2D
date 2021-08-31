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
    Player(const sf::Vector2f& initialPosition);
    virtual ~Player() = default;

    virtual void update(const sf::Time& frameTime);
    virtual void fixedUpdate(const sf::Time& frameTime);

    void setPortalGun(PortalGun& portalGun);

   private:
    const float CLICK_MIN_INTERVAL;

    float runAcceleration;
    float jumpPower;
    float floorDrag;
    float maxRunSpeed;

    sf::Clock clickIntervalClock;

    PortalGun* portalGun;

    engine::Transform& transform;
    engine::Physics& physics;
    engine::Collider& collider;
    engine::Sprite& sprite;
};
