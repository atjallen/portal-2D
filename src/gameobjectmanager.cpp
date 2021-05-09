#include "gameobjectmanager.h"

void GameObjectManager::remove(const std::string& name) {
    gameObjects.erase(name);
    visibleGameObjects.erase(name);
}

int GameObjectManager::getObjectCount() const {
    return gameObjects.size();
}

GameObject& GameObjectManager::get(const std::string& name) {
    return *gameObjects.at(name);
}

void GameObjectManager::drawAll(sf::RenderWindow& window) {
    for (auto& visibleGameObjectName : visibleGameObjects) {
        static_cast<VisibleGameObject*>(
            gameObjects[visibleGameObjectName].get())
            ->draw(window);
    }
}

void GameObjectManager::updateAll(const sf::Time& frameTime) {
    for (auto& stringObjectPair : gameObjects) {
        stringObjectPair.second->update(frameTime);
    }
}
