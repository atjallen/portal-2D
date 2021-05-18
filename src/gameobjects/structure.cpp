#include "structure.h"

Structure::Structure()
    : width(0),
      height(0),
      transform(createComponent<Transform>()),
      sprite(createComponent<Sprite>()) {}

void Structure::setDimensions(const sf::Vector2f& dimensions) {
    this->width = dimensions.x;
    this->height = dimensions.y;
    sprite.setDimensions(dimensions);
}
