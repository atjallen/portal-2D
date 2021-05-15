#include "floor.h"

#include "../config.h"

Floor::Floor()
    : width(0),
      height(0),
      transform(createComponent<Transform>()),
      collision(createComponent<Collision>()),
      sprite(createComponent<Sprite>()) {
    sprite.loadTexture(Config::getTextureFilename("Floor"));
    sprite.getTexture().setRepeated(true);
    collision.setKinematic(true);
}

void Floor::setDimensions(const sf::Vector2f& dimensions) {
    this->width = dimensions.x;
    this->height = dimensions.y;
    collision.setBoundingBoxDimensions(dimensions);
    sprite.setDimensions(dimensions);
}
