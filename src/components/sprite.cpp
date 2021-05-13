#include "sprite.h"

#include "../gameobjects/gameobject.h"

Sprite::Sprite(GameObject& gameObject)
    : Component(gameObject),
      loaded(false),
      transform(*gameObject.getComponent<Transform>()) {}

Sprite::Sprite(GameObject& gameObject, const std::string& filename)
    : Sprite(gameObject) {
    loadTexture(filename);
}

void Sprite::draw(sf::RenderWindow& window) {
    if (loaded) {
        window.draw(sprite);
    }
}

void Sprite::update(const sf::Time& frameTime) {
    if (loaded) {
        sprite.setPosition(transform.getPosition());
    }
}

sf::Texture& Sprite::getTexture() {
    return texture;
}

sf::Sprite& Sprite::getSprite() {
    return sprite;
}

void Sprite::setDimensions(const sf::Vector2f& dimensions) {
    auto boundingBox = sprite.getGlobalBounds();
    sprite.setTextureRect(sf::Rect<int>(boundingBox.left, boundingBox.top,
                                        dimensions.x, dimensions.y));
    resetOrigin();
}

void Sprite::loadTexture(const std::string& filename) {
    if (texture.loadFromFile(filename)) {
        this->filename = filename;
        sprite.setTexture(texture);
        resetOrigin();
        loaded = true;
    } else {
        this->filename = "";
        loaded = false;
    }
}

void Sprite::resetOrigin() {
    auto boundingBox = sprite.getGlobalBounds();
    sprite.setOrigin(boundingBox.width / 2, boundingBox.height / 2);
}
