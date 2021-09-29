#include "structure.h"

Structure::Structure(float width, float height, const sf::Vector2f& initialPosition)
    : width(width),
      height(height),
      transform(createComponent<engine::Transform>()),
      sprite(createComponent<engine::Sprite>()) {
    transform.setPosition(initialPosition);
    sprite.setDimensions(sf::Vector2f(width, height));
}
