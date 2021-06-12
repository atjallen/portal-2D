#include "portalgun.h"

#include <cmath>

#include "../game.h"
#include "../util/vector.h"

PortalGun::PortalGun() : transform(createComponent<Transform>()) {}

void PortalGun::draw(sf::RenderWindow& window) {
    GameObject::draw(window);

    // Calculate ray
    auto origin = transform.getPosition();
    auto angle = transform.getRotationRads();
    auto hitInfo = Game::raycast(origin, angle);
    auto rayLength = Game::RAYCAST_MAX;
    if (hitInfo.hit) {
        auto rayVector = hitInfo.hitPosition - origin;
        rayLength = util::vector::length(rayVector);
    }

    // Draw ray
    sf::RectangleShape rectangle(sf::Vector2f(rayLength, 5));
    rectangle.setPosition(transform.getPosition());
    rectangle.setRotation(transform.getRotation());
    rectangle.setFillColor(sf::Color::Red);
    window.draw(rectangle);
}