#include "collision.h"

#include <iostream>

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
        // Check whether collider has collided with the floor and if so stop
        // movement
        auto boundingBox = getBoundingBox();
        if (Game::isUnderFloor(boundingBox)) {
            physics.setVerticalVelocity(0);
            transform.setPositionY(transform.getPosition().y -
                                   Game::amountUnderFloor(boundingBox));
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
