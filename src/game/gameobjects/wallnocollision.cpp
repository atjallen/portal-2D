#include "wallnocollision.h"

WallNoCollision::WallNoCollision() {
    sprite.loadTexture(Config::getTextureFilename("Wall"));
    sprite.getTexture().setRepeated(true);
}
