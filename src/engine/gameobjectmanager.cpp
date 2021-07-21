#include "gameobjectmanager.h"

namespace engine {

void GameObjectManager::remove(const std::string& name) {
    nameToGameObjectPtr.erase(name);
}

void GameObjectManager::drawAll(sf::RenderWindow& window) {
    for (auto& nameGameObjectPtrPair : nameToGameObjectPtr) {
        nameGameObjectPtrPair.second->draw(window);
    }
}

void GameObjectManager::updateAll(const sf::Time& frameTime) {
    for (auto& nameGameObjectPtrPair : nameToGameObjectPtr) {
        nameGameObjectPtrPair.second->update(frameTime);
    }
}

void GameObjectManager::fixedUpdateAll(const sf::Time& frameTime) {
    for (auto& nameGameObjectPtrPair : nameToGameObjectPtr) {
        nameGameObjectPtrPair.second->fixedUpdate(frameTime);
    }
}

}  // namespace engine
