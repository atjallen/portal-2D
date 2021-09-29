#pragma once

#include "engine/components/collider.h"

namespace engine {

class BoxCollider : public Collider {
   public:
    BoxCollider(GameObject& gameObject);
    BoxCollider(GameObject& gameObject, float boxWidth, float boxHeight);
    virtual ~BoxCollider() = default;

    virtual bool isColliding(const Collider& other);
    virtual bool isTouchingBelow(const Collider& other);

    virtual std::vector<sf::Vector2f> getPoints() const;

   protected:
    virtual void handleCollision(const Collider& other);

   private:
    float boxWidth;
    float boxHeight;

    sf::FloatRect getColliderRect() const;
};

}  // namespace engine
