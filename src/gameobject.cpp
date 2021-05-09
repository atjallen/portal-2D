#include "gameobject.h"

void GameObject::setPosition(const sf::Vector2f& position) {
    this->position = position;
}

sf::Vector2f GameObject::getPosition() const {
    return position;
}

void GameObject::move(const sf::Vector2f& moveBy) {
    position += moveBy;
}
