#pragma once

#include <vector>

#include "engine/component.h"

#include "engine/components/physics.h"
#include "engine/components/transform.h"

namespace engine {

class Collider : public Component {
   public:
    Collider(GameObject& gameObject);
    virtual ~Collider() = default;

    void setKinematic(bool kinematic);

    virtual void fixedUpdate(const sf::Time& frameTime);

    virtual bool isColliding(const Collider& other) = 0;
    virtual bool isTouchingBelow(const Collider& other) = 0;

    virtual std::vector<sf::Vector2f> getPoints() const = 0;

   protected:
    bool kinematic;

    Transform& transform;
    Physics& physics;

    virtual void handleCollision(const Collider& other) = 0;
};

}  // namespace engine
