#include "wall.h"

Wall::Wall() {
    sprite.loadTexture(Config::getTextureFilename("Wall"));
    sprite.getTexture().setRepeated(true);
}
