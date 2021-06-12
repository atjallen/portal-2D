#include "transform.h"

#include <iostream>

#include "../util/vector.h"

Transform::Transform(GameObject& gameObject)
    : Component(gameObject), Transformable() {}

void Transform::setPositionX(float x) {
    setPosition(x, getPosition().y);
}

void Transform::setPositionY(float y) {
    setPosition(getPosition().x, y);
}

float Transform::getRotationRads() const {
    return util::vector::degToRad(Transformable::getRotation());
}

void Transform::setRotationRads(float angle) {
    Transformable::setRotation(util::vector::radToDeg(angle));
}

void Transform::rotateRads(float angle) {
    Transformable::rotate(util::vector::radToDeg(angle));
}

void Transform::lookAt(const sf::Vector2f& lookAtPosition) {
    auto lookAtVector = lookAtPosition - getPosition();
    auto lookAtAngle =
        util::vector::angleBetween(sf::Vector2f(1, 0), lookAtVector);
    setRotationRads(lookAtAngle);
}
