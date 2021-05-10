#include "sprite.h"

#include "gameobject.h"

Sprite::Sprite(GameObject& gameObject)
    : Component(gameObject),
      loaded(false),
      transform(*gameObject.getComponent<Transform>()) {}

Sprite::Sprite(GameObject& gameObject, const std::string& filename)
    : Sprite(gameObject) {
    loadTexture(filename);
}

void Sprite::loadTexture(const std::string& filename) {
    if (texture.loadFromFile(filename)) {
        this->filename = filename;
        sprite.setTexture(texture);
        sprite.setOrigin(sprite.getScale().x / 2, sprite.getScale().y / 2);
        loaded = true;
    } else {
        this->filename = "";
        loaded = false;
    }
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
