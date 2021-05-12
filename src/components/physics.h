#pragma once

#include "component.h"
#include "transform.h"

class Physics : public Component {
   public:
    Physics(GameObject& gameObject);
    virtual ~Physics() = default;

    virtual void fixedUpdate(const sf::Time& frameTime);

    void setGravity(float gravity);
    void setMaxHorizontalVelocity(float maxHorizontalVelocity);
    void setMaxVerticalVelocity(float maxVerticalVelocity);

    void setVerticalVelocity(float verticalVelocity);
    void addHorizontalVelocity(float addAmount);

   private:
    float gravity;
    float maxHorizontalVelocity;
    float maxVerticalVelocity;

    sf::Vector2f velocity;

    Transform& transform;
};
