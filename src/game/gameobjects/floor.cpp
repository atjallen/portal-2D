#include "floor.h"

Floor::Floor() {
    sprite.loadTexture(engine::Config::getTextureFilename("Floor"));
    sprite.getTexture().setRepeated(true);
}
