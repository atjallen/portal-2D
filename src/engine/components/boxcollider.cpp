#include "boxcollider.h"

#include "util/rect.h"
#include "util/type.h"

namespace engine {

BoxCollider::BoxCollider(GameObject& gameObject) : BoxCollider(gameObject, 0, 0) {}

BoxCollider::BoxCollider(GameObject& gameObject, float boxWidth, float boxHeight)
    : Collider(gameObject), boxWidth(boxWidth), boxHeight(boxHeight) {}

bool BoxCollider::isColliding(const Collider& other) {
    if (!util::isType<BoxCollider>(other)) {
        return false;
    }

    return this->getColliderRect().intersects(dynamic_cast<const BoxCollider&>(other).getColliderRect());
}

bool BoxCollider::isTouchingBelow(const Collider& other) {
    if (!util::isType<BoxCollider>(other)) {
        return false;
    }

    auto thisBoundingBox = this->getColliderRect();
    auto otherBoundingBox = dynamic_cast<const BoxCollider&>(other).getColliderRect();
    // clang-format off
        return
            // Bounding box is touching other bounding box below
            (thisBoundingBox.top + thisBoundingBox.height == otherBoundingBox.top)
            && !(
                // Bounding box is to the left of other bounding box
                thisBoundingBox.left + thisBoundingBox.width < otherBoundingBox.left
                // Bounding box is to the right of other bounding box
                || thisBoundingBox.left > otherBoundingBox.left + otherBoundingBox.width
            );
    // clang-format on
}

std::vector<sf::Vector2f> BoxCollider::getPoints() const {
    std::vector<sf::Vector2f> points;
    for (auto& point : util::rectToPoints(this->getColliderRect())) {
        points.push_back(point);
    }
    return points;
}

void BoxCollider::handleCollision(const Collider& other) {
    if (!util::isType<BoxCollider>(other)) {
        return;
    }

    sf::FloatRect intersection;
    if (this->getColliderRect().intersects(dynamic_cast<const BoxCollider&>(other).getColliderRect(), intersection)) {
        // To decide whether we are colliding horizontally or
        // vertically, we look at which dimension of the intersecting
        // rectangle is smaller and assume that this dimension is the
        // colliding one. This isn't perfect of course due to incredibly
        // thin bounding boxes but should do for now at least.
        //
        // TODO: Handle collision between two non-kinematic colliders
        if (intersection.width < intersection.height) {
            // Horizontal collision
            if (physics.getVelocity().x > 0) {
                // Rightwards collision
                transform.setPositionX(transform.getPosition().x - intersection.width);
            } else {
                // Leftwards collision
                transform.setPositionX(transform.getPosition().x + intersection.width);
            }
            physics.setHorizontalVelocity(0);
        } else {
            // Vertical collision
            if (physics.getVelocity().y > 0) {
                // Downwards collision
                transform.setPositionY(transform.getPosition().y - intersection.height);
            } else {
                // Upwards collision
                transform.setPositionY(transform.getPosition().y + intersection.height);
            }
            physics.setVerticalVelocity(0);
        }
    }
}

sf::FloatRect BoxCollider::getColliderRect() const {
    float left = transform.getPosition().x - (boxWidth / 2);
    float top = transform.getPosition().y - (boxHeight / 2);
    return sf::FloatRect(left, top, boxWidth, boxHeight);
}

}  // namespace engine
