#include "portal.h"

#include "engine/components/boxcollider.h"

Portal::Portal()
    : transform(createComponent<engine::Transform>()),
      sprite(createComponent<engine::Sprite>(engine::Config::getTextureFilename("Portal"))),
      collider(createComponent<engine::BoxCollider>(10, 90)) {
    sprite.getSprite().setColor(sf::Color::Blue);
    auto spriteBoundingBox = sprite.getSprite().getGlobalBounds();
    collider.setKinematic(true);
}

void Portal::setColor(const sf::Color& color) {
    sprite.getSprite().setColor(color);
}
