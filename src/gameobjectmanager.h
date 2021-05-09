#pragma once

#include <functional>
#include <map>
#include <memory>
#include <set>

#include "gameobject.h"
#include "visiblegameobject.h"

class GameObjectManager {
   public:
    GameObjectManager() = default;
    ~GameObjectManager() = default;

    template <typename GameObjectType>
    void addGameObject(const std::string& name,
                       const GameObjectType& gameObject);
    template <typename VisibleGameObjectType>
    void addVisibleGameObject(const std::string& name,
                              const VisibleGameObjectType& visibleGameObject);
    void remove(const std::string& name);
    GameObject& get(const std::string& name);
    int getObjectCount() const;

    void drawAll(sf::RenderWindow& window);
    void updateAll(const sf::Time& frameTime);

   private:
    std::map<std::string, std::unique_ptr<GameObject>> gameObjects;
    std::set<std::string> visibleGameObjects;
};

// FIXME: This can probably be better
template <typename GameObjectType>
void GameObjectManager::addGameObject(const std::string& name,
                                      const GameObjectType& gameObject) {
    static_assert(std::is_base_of<GameObject, GameObjectType>::value,
                  "Derived not derived from base");
    gameObjects[name] = std::make_unique<GameObjectType>(gameObject);
}

template <typename VisibleGameObjectType>
void GameObjectManager::addVisibleGameObject(
    const std::string& name,
    const VisibleGameObjectType& visibleGameObject) {
    static_assert(
        std::is_base_of<VisibleGameObject, VisibleGameObjectType>::value,
        "Derived not derived from base");
    gameObjects[name] =
        std::make_unique<VisibleGameObjectType>(visibleGameObject);
    visibleGameObjects.insert(name);
}
