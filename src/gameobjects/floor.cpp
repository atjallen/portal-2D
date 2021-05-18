#include "floor.h"

Floor::Floor() {
    sprite.loadTexture(Config::getTextureFilename("Floor"));
    sprite.getTexture().setRepeated(true);
}
