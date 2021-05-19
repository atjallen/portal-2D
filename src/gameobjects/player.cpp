#include "player.h"

#include <cmath>

#include "../game.h"

Player::Player()
    : runAcceleration(0.5f),
      jumpPower(10.0f),
      floorDrag(0.5f),
      maxRunSpeed(10.0f),
      transform(createComponent<Transform>()),
      physics(createComponent<Physics>()),
      collision(createComponent<Collision>()),
      sprite(createComponent<Sprite>()) {
    sprite.loadTexture(Config::getTextureFilename("Player"));
    sprite.getSprite().setColor(sf::Color::Red);
    auto spriteBoundingBox = sprite.getSprite().getGlobalBounds();
    collision.setBoundingBoxDimensions(
        sf::Vector2f(spriteBoundingBox.width, spriteBoundingBox.height));
}

void Player::fixedUpdate(const sf::Time& frameTime) {
    GameObject::fixedUpdate(frameTime);

    bool movingLeftOrRight = false;

    // Move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        physics.addHorizontalVelocity(-runAcceleration);
        movingLeftOrRight = true;
    }

    // Move right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        physics.addHorizontalVelocity(runAcceleration);
        movingLeftOrRight = true;
    }

    if (Game::isOnFloor(*this)) {
        // Jump
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
            Game::isOnFloor(*this)) {
            physics.addVerticalVelocity(-jumpPower);
        }

        // Slow player if not moving
        if (!movingLeftOrRight) {
            if (physics.getVelocity().x > 0) {
                // Moving to the right
                physics.addHorizontalVelocity(-floorDrag);

                // If now moving to the left, stop
                if (physics.getVelocity().x < 0) {
                    physics.setHorizontalVelocity(0);
                }
            } else if (physics.getVelocity().x < 0) {
                // Moving to the left
                physics.addHorizontalVelocity(floorDrag);

                // If now moving to the right, stop
                if (physics.getVelocity().x > 0) {
                    physics.setHorizontalVelocity(0);
                }
            }
        }
    }

    // Limit player horizontal speed
    if (std::abs(physics.getVelocity().x) > maxRunSpeed) {
        if (physics.getVelocity().x > 0) {
            physics.setHorizontalVelocity(maxRunSpeed);
        } else {
            physics.setHorizontalVelocity(-maxRunSpeed);
        }
    }
}
