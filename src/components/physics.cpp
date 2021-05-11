#include "physics.h"

#include "../gameobjects/gameobject.h"

Physics::Physics(GameObject& gameObject)
    : Component(gameObject),
      gravity(0.5f),
      transform(*gameObject.getComponent<Transform>()) {}

void Physics::fixedUpdate(const sf::Time& frameTime) {
    // Move transform by velocity
    transform.move(velocity);

    // Apply gravity
    velocity += sf::Vector2f(0, 1) * gravity;
}

void Physics::setGravity(float gravity) {
    this->gravity = gravity;
}

void Physics::setVerticalVelocity(float verticalVelocity) {
    velocity.y = verticalVelocity;
}
