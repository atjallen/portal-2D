#include "collider.h"

#include "../game.h"
#include "../gameobjects/gameobject.h"

Collider::Collider(GameObject& gameObject)
    : Component(gameObject),
      boundingBoxWidth(0),
      boundingBoxHeight(0),
      kinematic(false),
      transform(*gameObject.getComponent<Transform>()),
      physics(*gameObject.getComponent<Physics>()) {}

void Collider::fixedUpdate(const sf::Time& frameTime) {
    if (!kinematic) {
        auto colliders = Game::getAllColliderComponents();
        for (auto* colliderPtr : colliders) {
            sf::Rect<float> intersection;
            if (colliderPtr != this &&
                this->getBoundingBox().intersects(
                    colliderPtr->getBoundingBox(), intersection)) {
                // Resolve collider
                //
                // TODO: Handle collider between two non-kinematic colliders
                //
                // To decide whether we are colliding horizontally or
                // vertically, we look at which dimension of the intersecting
                // rectangle is smaller and assume that this dimension is the
                // colliding one. This isn't perfect of course due to incredibly
                // thin bounding boxes but should do for now at least.
                if (intersection.width < intersection.height) {
                    // Horizontal collider
                    if (physics.getVelocity().x > 0) {
                        // Rightwards collider
                        transform.setPositionX(transform.getPosition().x -
                                               intersection.width);
                    } else {
                        // Leftwards collider
                        transform.setPositionX(transform.getPosition().x +
                                               intersection.width);
                    }
                    physics.setHorizontalVelocity(0);
                } else {
                    // Vertical collider
                    if (physics.getVelocity().y > 0) {
                        // Downwards collider
                        transform.setPositionY(transform.getPosition().y -
                                               intersection.height);
                    } else {
                        // Upwards collider
                        transform.setPositionY(transform.getPosition().y +
                                               intersection.height);
                    }
                    physics.setVerticalVelocity(0);
                }
            }
        }
    }
}

sf::Rect<float> Collider::getBoundingBox() const {
    auto position = transform.getPosition();
    return sf::Rect<float>(position.x - (boundingBoxWidth / 2),
                           position.y - (boundingBoxHeight / 2),
                           boundingBoxWidth, boundingBoxHeight);
}

void Collider::setBoundingBoxDimensions(const sf::Vector2f& dimensions) {
    boundingBoxWidth = dimensions.x;
    boundingBoxHeight = dimensions.y;
}

void Collider::setKinematic(bool kinematic) {
    this->kinematic = kinematic;
}

bool Collider::isColliding(const Collider& other) {
    return getBoundingBox().intersects(other.getBoundingBox());
}

bool Collider::isTouchingBelow(const Collider& other) {
    auto thisBoundingBox = getBoundingBox();
    auto otherBoundingBox = other.getBoundingBox();
    // clang-format off
    return
        (thisBoundingBox.top + thisBoundingBox.height == otherBoundingBox.top) // Bounding box is touching other bounding box below
        && !(
            thisBoundingBox.left + thisBoundingBox.width < otherBoundingBox.left // Bounding box is to the left of other bounding box
            || thisBoundingBox.left > otherBoundingBox.left + otherBoundingBox.width // Bounding box is to the right of other bounding box
        );
    // clang-format on`
}
