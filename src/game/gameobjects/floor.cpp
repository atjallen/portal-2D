#include "floor.h"

Floor::Floor(float width, float height, const sf::Vector2f& initialPosition)
    : CollisionStructure(width, height, initialPosition) {
    sprite.loadTexture(engine::Config::getTextureFilename("Floor"));
    sprite.getTexture().setRepeated(true);
}
