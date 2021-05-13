#include "collision.h"

#include <iostream>

#include "../game.h"
#include "../gameobjects/gameobject.h"

Collision::Collision(GameObject& gameObject)
    : Component(gameObject),
      kinematic(false),
      transform(*gameObject.getComponent<Transform>()),
      physics(*gameObject.getComponent<Physics>()) {}

void Collision::update(const sf::Time& frameTime) {
    // Update bounding box position according to transform
    boundingBox.left = transform.getPosition().x - (boundingBox.width / 2);
    boundingBox.top = transform.getPosition().y - (boundingBox.height / 2);
}

void Collision::fixedUpdate(const sf::Time& frameTime) {
    if (!kinematic) {
        // Check whether collider has collided with the floor and if so stop
        // movement
        if (Game::isUnderFloor(boundingBox)) {
            physics.setVerticalVelocity(0);
            transform.setPositionY(transform.getPosition().y -
                                   Game::amountUnderFloor(boundingBox));
        }
    }
}

sf::Rect<float> Collision::getBoundingBox() const {
    return boundingBox;
}

void Collision::setBoundingBoxDimensions(const sf::Vector2f& dimensions) {
    boundingBox.width = dimensions.x;
    boundingBox.height = dimensions.y;
}

void Collision::setKinematic(bool kinematic) {
    this->kinematic = kinematic;
}
