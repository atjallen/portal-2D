#include "wall.h"

Wall::Wall(float width, float height, const sf::Vector2f& initialPosition)
    : CollisionStructure(width, height, initialPosition) {
    sprite.loadTexture(engine::Config::getTextureFilename("Wall"));
    sprite.getTexture().setRepeated(true);
}
