#include "component.h"

Component::Component(GameObject& gameObject) : gameObject(gameObject) {}

void Component::draw(sf::RenderWindow& window) {
    // Do nothing
}

void Component::update(const sf::Time& frameTime) {
    // Do nothing
}

void Component::fixedUpdate(const sf::Time& frameTime) {
    // Do nothing
}
