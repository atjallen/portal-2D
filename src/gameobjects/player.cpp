#include "player.h"

#include "../game.h"

Player::Player()
    : runAcceleration(0.5f),
      jumpPower(10.0f),
      transform(createComponent<Transform>()),
      physics(createComponent<Physics>()),
      collision(createComponent<Collision>()),
      sprite(createComponent<Sprite>()) {
    sprite.loadTexture("res/player.png");
    sprite.getSprite().setColor(sf::Color::Red);
    auto spriteBoundingBox = sprite.getSprite().getGlobalBounds();
    collision.setBoundingBoxDimensions(
        sf::Vector2f(spriteBoundingBox.width, spriteBoundingBox.height));
}

void Player::fixedUpdate(const sf::Time& frameTime) {
    GameObject::fixedUpdate(frameTime);

    // Move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        physics.addHorizontalVelocity(-runAcceleration);
    }

    // Move right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        physics.addHorizontalVelocity(runAcceleration);
    }

    // Jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
        Game::isOnFloor(collision.getBoundingBox())) {
        physics.addVerticalVelocity(-jumpPower);
    }
}
