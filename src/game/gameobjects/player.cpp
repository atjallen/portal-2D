#include "player.h"

#include <cmath>

#include "../../engine/engine.h"

#include "../util/collision.h"

Player::Player()
    : runAcceleration(0.5f),
      jumpPower(10.0f),
      floorDrag(0.5f),
      maxRunSpeed(10.0f),
      portalGun(nullptr),
      transform(createComponent<engine::Transform>()),
      physics(createComponent<engine::Physics>()),
      collider(createComponent<engine::Collider>()),
      sprite(createComponent<engine::Sprite>()) {
    sprite.loadTexture(engine::Config::getTextureFilename("Player"));
    sprite.getSprite().setColor(sf::Color::Red);
    auto spriteBoundingBox = sprite.getSprite().getGlobalBounds();
    collider.setBoundingBoxDimensions(
        sf::Vector2f(spriteBoundingBox.width, spriteBoundingBox.height));
}

void Player::update(const sf::Time& frameTime) {
    GameObject::update(frameTime);

    if (portalGun) {
        portalGun->getComponent<engine::Transform>()->setPosition(
            transform.getPosition() + sf::Vector2f(30, 0));
        portalGun->getComponent<engine::Transform>()->lookAt(
            sf::Vector2f(engine::Engine::getMousePosition()));
    }
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

    if (gameutil::isOnFloor(*this)) {
        // Jump
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
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

void Player::setPortalGun(PortalGun& portalGun) {
    this->portalGun = &portalGun;
}