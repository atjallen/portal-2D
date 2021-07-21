#include "ceiling.h"

Ceiling::Ceiling() {
    sprite.loadTexture(engine::Config::getTextureFilename("Ceiling"));
    sprite.getTexture().setRepeated(true);
}
