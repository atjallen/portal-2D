#include "ceiling.h"

Ceiling::Ceiling() {
    sprite.loadTexture(Config::getTextureFilename("Ceiling"));
    sprite.getTexture().setRepeated(true);
}
