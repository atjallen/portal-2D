#include "ceiling.h"

Ceiling::Ceiling(float width, float height, const sf::Vector2f& initialPosition)
    : CollisionStructure(width, height, initialPosition) {
    sprite.loadTexture(engine::Config::getTextureFilename("Ceiling"));
    sprite.getTexture().setRepeated(true);
}
