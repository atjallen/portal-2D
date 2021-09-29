#include "convexshapecollider.h"

#include "util/shape.h"
#include "util/type.h"

namespace engine {

ConvexShapeCollider::ConvexShapeCollider(GameObject& gameObject) : ConvexShapeCollider(gameObject, sf::ConvexShape()) {}

ConvexShapeCollider::ConvexShapeCollider(GameObject& gameObject, const sf::ConvexShape& localShape)
    : Collider(gameObject), localShape(localShape) {}

bool ConvexShapeCollider::isColliding(const Collider& other) {
    if (!util::isType<ConvexShapeCollider>(other)) {
        return false;
    }

    return util::doesIntersect(this->getColliderShape(),
                               dynamic_cast<const ConvexShapeCollider&>(other).getColliderShape());
}

std::vector<sf::Vector2f> ConvexShapeCollider::getPoints() const {
    return util::getPointsTransformed(getColliderShape());
}

sf::ConvexShape ConvexShapeCollider::getColliderShape() const {
    sf::ConvexShape colliderShape(localShape);
    colliderShape.setScale(transform.getScale());
    colliderShape.setRotation(transform.getRotation());
    colliderShape.setPosition(transform.getPosition());
    return colliderShape;
}

}  // namespace engine
