#include "portalgun.h"

#include <cmath>

#include "engine/engine.h"

#include "game/gameobjects/portal.h"

#include "util/line.h"
#include "util/units.h"
#include "util/vector.h"

PortalGun::PortalGun() : transform(createComponent<engine::Transform>()) {}

void PortalGun::draw(sf::RenderWindow& window) {
    GameObject::draw(window);

    auto rayLength = engine::raycast::RAYCAST_MAX;

    auto hitInfo = raycast();
    if (hitInfo.hit) {
        auto origin = transform.getPosition();
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

void PortalGun::firePortalA() {
    firePortal("PortalA", sf::Color::Cyan);
}

void PortalGun::firePortalB() {
    firePortal("PortalB", sf::Color(255, 165, 0));  // Orange
}

void PortalGun::firePortal(const std::string& name, const sf::Color& color) {
    auto hitInfo = raycast();
    if (hitInfo.hit) {
        auto& portal = engine::Engine::createGameObject<Portal>(name);
        portal.getComponent<engine::Transform>()->setPosition(hitInfo.hitPosition);
        portal.setColor(color);
        float hitSegmentAngle = util::vectorToAngle(hitInfo.segment.getDirection());
        portal.getComponent<engine::Transform>()->setRotationRads(hitSegmentAngle + M_PI / 2.0);
    }
}

engine::raycast::HitInfo PortalGun::raycast() {
    auto& player = engine::Engine::getGameObject("Player");
    auto origin = transform.getPosition();
    auto angle = transform.getRotationRads();
    return engine::raycast::raycast(origin, angle, {player.getComponent<engine::Collider>()});
}
