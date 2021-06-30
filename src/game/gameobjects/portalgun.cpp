#include "portalgun.h"

#include <cmath>

#include "../../engine/engine.h"
#include "../../engine/raycast.h"
#include "../../util/vector.h"

PortalGun::PortalGun() : transform(createComponent<Transform>()) {}

void PortalGun::draw(sf::RenderWindow& window) {
    GameObject::draw(window);

    auto& player = Engine::getGameObject("Player");

    // Calculate ray
    auto origin = transform.getPosition();
    auto angle = transform.getRotationRads();
    auto hitInfo =
        raycast::raycast(origin, angle, {player.getComponent<Collider>()});
    auto rayLength = raycast::RAYCAST_MAX;
    if (hitInfo.hit) {
        auto rayVector = hitInfo.hitPosition - origin;
        rayLength = util::length(rayVector);
    }

    // Draw ray
    sf::RectangleShape rectangle(sf::Vector2f(rayLength, 5));
    rectangle.setPosition(transform.getPosition());
    rectangle.setRotation(transform.getRotation());
    rectangle.setFillColor(sf::Color::Red);
    window.draw(rectangle);
}
