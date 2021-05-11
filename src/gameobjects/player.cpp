#include "player.h"

#include "../components/collision.h"
#include "../components/physics.h"
#include "../components/sprite.h"
#include "../components/transform.h"

Player::Player() /*
        velocity(0),
        maxVelocity(600.0f),
        acceleration(10.0f),
        drag(2.0f)*/
{
    createComponent<Transform>();

    createComponent<Physics>();

    auto& sprite = createComponent<Sprite>();
    sprite.loadTexture("res/player.png");

    auto& collision = createComponent<Collision>();
    collision.setBoundingBox(sprite.getBoundingBox());
}

void Player::update(const sf::Time& frameTime) {
    GameObject::update(frameTime);

    //// Accelerate according to player input
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    //    velocity -= acceleration;
    //}

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    //    velocity += acceleration;
    //}

    //// Restrict velocity to max and min values
    // if (velocity > maxVelocity) {
    //    velocity = maxVelocity;
    //}

    // if (velocity < -maxVelocity) {
    //    velocity = -maxVelocity;
    //}

    //// Apply drag
    //// velocity /= drag;

    //// Move player
    // move(sf::Vector2f(1, 0) * velocity * frameTime.asSeconds());
}
