#include "physics.h"

#include <cmath>
#include <limits>

#include "engine/gameobject.h"

namespace engine {

Physics::Physics(GameObject& gameObject)
    : Component(gameObject),
      gravity(0.5f),
      maxHorizontalVelocity(std::numeric_limits<float>::max()),
      maxVerticalVelocity(20.0f),
      transform(*gameObject.getComponent<Transform>()) {}

void Physics::fixedUpdate(const sf::Time& frameTime) {
    // Move transform by velocity
    transform.move(velocity);

    // Restrict velocity
    if (std::abs(velocity.x) > maxHorizontalVelocity) {
        velocity.x = velocity.x > 0 ? maxHorizontalVelocity : -maxHorizontalVelocity;
    }

    if (std::abs(velocity.y) > maxVerticalVelocity) {
        velocity.y = velocity.y > 0 ? maxVerticalVelocity : -maxVerticalVelocity;
    }

    // Apply gravity
    velocity += sf::Vector2f(0, 1) * gravity;
}

void Physics::setGravity(float gravity) {
    this->gravity = gravity;
}

void Physics::setMaxHorizontalVelocity(float maxHorizontalVelocity) {
    this->maxHorizontalVelocity = maxHorizontalVelocity;
}

void Physics::setMaxVerticalVelocity(float maxVerticalVelocity) {
    this->maxVerticalVelocity = maxVerticalVelocity;
}

sf::Vector2f Physics::getVelocity() {
    return velocity;
}

void Physics::setHorizontalVelocity(float horizontalVelocity) {
    velocity.x = horizontalVelocity;
}

void Physics::setVerticalVelocity(float verticalVelocity) {
    velocity.y = verticalVelocity;
}

void Physics::addHorizontalVelocity(float addAmount) {
    velocity.x += addAmount;
}

void Physics::addVerticalVelocity(float addAmount) {
    velocity.y += addAmount;
}

}  // namespace engine
