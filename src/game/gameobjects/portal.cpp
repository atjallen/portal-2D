#include "portal.h"

Portal::Portal()
    : transform(createComponent<engine::Transform>()),
      sprite(createComponent<engine::Sprite>(engine::Config::getTextureFilename("Portal"))),
      collider(createComponent<engine::Collider>()) {
    sprite.getSprite().setColor(sf::Color::Blue);
    auto spriteBoundingBox = sprite.getSprite().getGlobalBounds();
    collider.setBoundingBoxDimensions(sf::Vector2f(spriteBoundingBox.width, spriteBoundingBox.height));
    collider.setKinematic(true);
}

void Portal::setColor(const sf::Color& color) {
    sprite.getSprite().setColor(color);
}
