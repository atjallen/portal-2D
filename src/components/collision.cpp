#include "collision.h"

#include <iostream>

#include "../game.h"
#include "../gameobjects/gameobject.h"

Collision::Collision(GameObject& gameObject)
    : Component(gameObject),
      transform(*gameObject.getComponent<Transform>()),
      physics(*gameObject.getComponent<Physics>()) {}

void Collision::update(const sf::Time& frameTime) {
    // Update bounding box position according to transform
    boundingBox.left = transform.getPosition().x;
    boundingBox.top = transform.getPosition().y;
}

void Collision::fixedUpdate(const sf::Time& frameTime) {
    // Check whether collider has collided with the floor and if so stop movement
    if (Game::isUnderFloor(boundingBox)) {
        physics.setVerticalVelocity(0);
        transform.setPositionY(transform.getPosition().y -
                               Game::amountUnderFloor(boundingBox));
    }
}

sf::Rect<float> Collision::getBoundingBox() const {
    return boundingBox;
}

void Collision::setBoundingBox(const sf::Rect<float>& boundingBox) {
    this->boundingBox = boundingBox;
}
