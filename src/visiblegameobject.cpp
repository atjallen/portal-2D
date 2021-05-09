#include "visiblegameobject.h"

VisibleGameObject::VisibleGameObject() : GameObject(), loaded(false) {}

void VisibleGameObject::setPosition(const sf::Vector2f& position) {
    GameObject::setPosition(position);

    if (loaded) {
        sprite.setPosition(position);
    }
}

void VisibleGameObject::move(const sf::Vector2f& moveBy) {
    GameObject::move(moveBy);

    if (loaded) {
        sprite.move(moveBy);
    }
}

void VisibleGameObject::load(const std::string& filename) {
    if (texture.loadFromFile(filename)) {
        this->filename = filename;
        sprite.setTexture(texture);
        loaded = true;
    } else {
        this->filename = "";
        loaded = false;
    }
}

void VisibleGameObject::draw(sf::RenderWindow& window) {
    if (loaded) {
        window.draw(sprite);
    }
}
