#include "player.h"

Player::Player()
    : acceleration(0.5f),
      transform(createComponent<Transform>()),
      physics(createComponent<Physics>()),
      collision(createComponent<Collision>()),
      sprite(createComponent<Sprite>()) {
    sprite.loadTexture("res/player.png");
    collision.setBoundingBox(sprite.getBoundingBox());
}

void Player::fixedUpdate(const sf::Time& frameTime) {
    GameObject::fixedUpdate(frameTime);

    // Accelerate according to player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        physics.addHorizontalVelocity(-acceleration);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        physics.addHorizontalVelocity(acceleration);
    }
}
