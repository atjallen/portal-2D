#pragma once

#include "engine/components/collider.h"

namespace engine {

class ConvexShapeCollider : public Collider {
   public:
    ConvexShapeCollider(GameObject& gameObject);
    ConvexShapeCollider(GameObject& gameObject, const sf::ConvexShape& localShape);
    virtual ~ConvexShapeCollider() = default;

    virtual bool isColliding(const Collider& other);

    virtual std::vector<sf::Vector2f> getPoints() const;

   private:
    sf::ConvexShape localShape;

    sf::ConvexShape getColliderShape() const;
};

}  // namespace engine
