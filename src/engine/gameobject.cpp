#include "gameobject.h"

namespace engine {

void GameObject::draw(sf::RenderWindow& window) {
    for (auto& componentPtr : componentPtrs) {
        componentPtr->draw(window);
    }
}

void GameObject::update(const sf::Time& frameTime) {
    for (auto& componentPtr : componentPtrs) {
        componentPtr->update(frameTime);
    }
}

void GameObject::fixedUpdate(const sf::Time& frameTime) {
    for (auto& componentPtr : componentPtrs) {
        componentPtr->fixedUpdate(frameTime);
    }
}

}  // namespace engine
