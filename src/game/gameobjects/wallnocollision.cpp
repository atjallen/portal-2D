#include "wallnocollision.h"

WallNoCollision::WallNoCollision(float width, float height, const sf::Vector2f& initialPosition)
    : Structure(width, height, initialPosition) {
    sprite.loadTexture(engine::Config::getTextureFilename("Wall"));
    sprite.getTexture().setRepeated(true);
}
