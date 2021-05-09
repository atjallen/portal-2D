#include "player.h"

#include <cassert>

Player::Player()
    : VisibleGameObject(),
      velocity(0),
      maxVelocity(600.0f),
      acceleration(10.0f),
      drag(2.0f) {
    load("res/player.png");
    assert(loaded);

    sprite.setOrigin(sprite.getScale().x / 2, sprite.getScale().y / 2);
}

void Player::update(const sf::Time& frameTime) {
    // Accelerate according to player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity -= acceleration;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity += acceleration;
    }

    // Restrict velocity to max and min values
    if (velocity > maxVelocity) {
        velocity = maxVelocity;
    }

    if (velocity < -maxVelocity) {
        velocity = -maxVelocity;
    }

    // Apply drag
    // velocity /= drag;

    // Move player
    move(sf::Vector2f(1, 0) * velocity * frameTime.asSeconds());
}
