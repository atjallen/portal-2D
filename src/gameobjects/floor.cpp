#include "floor.h"

Floor::Floor()
    : width(0),
      height(0),
      transform(createComponent<Transform>()),
      collision(createComponent<Collision>()),
      sprite(createComponent<Sprite>()) {
    sprite.loadTexture("res/floor.png");
    sprite.getTexture().setRepeated(true);
}

void Floor::setDimensions(const sf::Vector2f dimensions) {
    this->width = dimensions.x;
    this->height = dimensions.y;
    sf::Rect<float> boundingBox(transform.getPosition().x,
                                transform.getPosition().y, this->width,
                                this->height);
    collision.setBoundingBox(boundingBox);
    sprite.getSprite().setTextureRect(sf::Rect<int>(boundingBox));
}
