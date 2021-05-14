#include "collision.h"

#include "../game.h"
#include "../gameobjects/gameobject.h"

Collision::Collision(GameObject& gameObject)
    : Component(gameObject),
      boundingBoxWidth(0),
      boundingBoxHeight(0),
      kinematic(false),
      transform(*gameObject.getComponent<Transform>()),
      physics(*gameObject.getComponent<Physics>()) {}

void Collision::fixedUpdate(const sf::Time& frameTime) {
    if (!kinematic) {
        auto collisions = Game::getAllCollisionComponents();
        for (auto& collisionWrap : collisions) {
            auto& collision = collisionWrap.get();
            sf::Rect<float> intersection;
            if (&collision != this &&
                this->getBoundingBox().intersects(collision.getBoundingBox(),
                                                  intersection)) {
                // Resolve collision
                //
                // TODO: Handle collision between two non-kinematic colliders
                //
                // To decide whether we are colliding horizontally or
                // vertically, we look at which dimension of the intersecting
                // rectangle is smaller and assume that this dimension is the
                // colliding one. This isn't perfect of course due to incredibly
                // thin bounding boxes but should do for now at least.
                if (intersection.width < intersection.height) {
                    // Horizontal collision
                    if (physics.getVelocity().x > 0) {
                        // Rightwards collision
                        transform.setPositionX(transform.getPosition().x -
                                               intersection.width);
                    } else {
                        // Leftwards collision
                        transform.setPositionX(transform.getPosition().x +
                                               intersection.width);
                    }
                    physics.setHorizontalVelocity(0);
                } else {
                    // Vertical collision
                    if (physics.getVelocity().y > 0) {
                        // Downwards collision
                        transform.setPositionY(transform.getPosition().y -
                                               intersection.height);
                    } else {
                        // Upwards collision
                        transform.setPositionY(transform.getPosition().y +
                                               intersection.height);
                    }
                    physics.setVerticalVelocity(0);
                }
            }
        }
    }
}

sf::Rect<float> Collision::getBoundingBox() const {
    auto position = transform.getPosition();
    return sf::Rect<float>(position.x - (boundingBoxWidth / 2),
                           position.y - (boundingBoxHeight / 2),
                           boundingBoxWidth, boundingBoxHeight);
}

void Collision::setBoundingBoxDimensions(const sf::Vector2f& dimensions) {
    boundingBoxWidth = dimensions.x;
    boundingBoxHeight = dimensions.y;
}

void Collision::setKinematic(bool kinematic) {
    this->kinematic = kinematic;
}

bool Collision::isColliding(const Collision& other) {
    return getBoundingBox().intersects(other.getBoundingBox());
}

bool Collision::isTouchingBelow(const Collision& other) {
    auto thisBoundingBox = getBoundingBox();
    auto otherBoundingBox = other.getBoundingBox();
    return thisBoundingBox.top + thisBoundingBox.height == otherBoundingBox.top;
}
