#include "wallnocollision.h"

WallNoCollision::WallNoCollision() {
    sprite.loadTexture(engine::Config::getTextureFilename("Wall"));
    sprite.getTexture().setRepeated(true);
}
