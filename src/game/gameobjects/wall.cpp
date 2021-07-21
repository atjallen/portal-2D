#include "wall.h"

Wall::Wall() {
    sprite.loadTexture(engine::Config::getTextureFilename("Wall"));
    sprite.getTexture().setRepeated(true);
}
