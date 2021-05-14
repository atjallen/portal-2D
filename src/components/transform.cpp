#include "transform.h"

Transform::Transform(GameObject& gameObject)
    : Transform(gameObject, sf::Vector2f()) {}

Transform::Transform(GameObject& gameObject, const sf::Vector2f& initPosition)
    : Component(gameObject), position(initPosition) {}

sf::Vector2f Transform::getPosition() const {
    return position;
}

void Transform::setPosition(const sf::Vector2f& position) {
    this->position = position;
}

void Transform::setPositionX(float x) {
    position.x = x;
}

void Transform::setPositionY(float y) {
    position.y = y;
}

void Transform::move(const sf::Vector2f& moveBy) {
    position += moveBy;
}
