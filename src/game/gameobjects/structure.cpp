#include "structure.h"

Structure::Structure()
    : width(0), height(0), transform(createComponent<engine::Transform>()), sprite(createComponent<engine::Sprite>()) {}

Structure::Structure(const sf::Vector2f& initialPosition, const sf::Vector2f& dimensions) : Structure() {
    transform.setPosition(initialPosition);
    setDimensions(dimensions);
}

void Structure::setDimensions(const sf::Vector2f& dimensions) {
    this->width = dimensions.x;
    this->height = dimensions.y;
    sprite.setDimensions(dimensions);
}
