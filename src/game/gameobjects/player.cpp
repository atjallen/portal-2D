#include "player.h"

#include <cmath>

#include "engine/engine.h"

#include "engine/components/boxcollider.h"

#include "game/util/collision.h"

Player::Player()
    : CLICK_MIN_INTERVAL(0.5),
      runAcceleration(0.5f),
      jumpPower(10.0f),
      floorDrag(0.5f),
      maxRunSpeed(10.0f),
      portalGun(nullptr),
      transform(createComponent<engine::Transform>()),
      physics(createComponent<engine::Physics>()),
      collider(createComponent<engine::BoxCollider>(50, 100)),
      sprite(createComponent<engine::Sprite>(engine::Config::getTextureFilename("Player"))) {
    sprite.getSprite().setColor(sf::Color::Red);
}

Player::Player(const sf::Vector2f& initialPosition) : Player() {
    transform.setPosition(initialPosition);
}

void Player::update(const sf::Time& frameTime) {
    GameObject::update(frameTime);

    if (portalGun) {
        portalGun->getComponent<engine::Transform>()->setPosition(transform.getPosition() + sf::Vector2f(30, 0));
        portalGun->getComponent<engine::Transform>()->lookAt(sf::Vector2f(engine::Engine::getMousePosition()));
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

    // Fire portal
    if (clickIntervalClock.getElapsedTime().asSeconds() > CLICK_MIN_INTERVAL) {
        bool leftClickPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        bool rightClickPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);

        if (leftClickPressed) {
            portalGun->firePortalA();
        } else if (rightClickPressed) {
            portalGun->firePortalB();
        }

        if (leftClickPressed || rightClickPressed) {
            clickIntervalClock.restart();
        }
    }
}

void Player::setPortalGun(PortalGun& portalGun) {
    this->portalGun = &portalGun;
}
