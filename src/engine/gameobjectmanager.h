#pragma once

#include <functional>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "gameobject.h"

namespace engine {

class GameObjectManager {
   public:
    GameObjectManager() = default;
    ~GameObjectManager() = default;

    template <typename GameObjectType = GameObject, typename... ConstructorArgs>
    GameObjectType& create(const std::string& name, const ConstructorArgs&... constructorArgs);
    template <typename GameObjectType = GameObject>
    GameObjectType& get(const std::string& name);
    template <typename GameObjectType>
    std::set<GameObjectType*> getAll();
    template <typename ComponentType>
    std::set<ComponentType*> getAllComponents();
    void remove(const std::string& name);

    void drawAll(sf::RenderWindow& window);
    void updateAll(const sf::Time& frameTime);
    void fixedUpdateAll(const sf::Time& frameTime);

   private:
    std::map<std::string, std::unique_ptr<GameObject>> nameToGameObjectPtr;
};

template <typename GameObjectType, typename... ConstructorArgs>
inline GameObjectType& GameObjectManager::create(const std::string& name, const ConstructorArgs&... constructorArgs) {
    static_assert(std::is_base_of<GameObject, GameObjectType>::value, "Class not subclass of GameObject");
    nameToGameObjectPtr[name] = std::make_unique<GameObjectType>(constructorArgs...);
    return static_cast<GameObjectType&>(*nameToGameObjectPtr[name]);
}

template <typename GameObjectType>
inline GameObjectType& GameObjectManager::get(const std::string& name) {
    return static_cast<GameObjectType&>(*nameToGameObjectPtr.at(name));
}

template <>
inline std::set<GameObject*> GameObjectManager::getAll() {
    std::set<GameObject*> gameObjects;
    for (auto& nameGameObjectPtrPair : nameToGameObjectPtr) {
        gameObjects.insert(nameGameObjectPtrPair.second.get());
    }
    return gameObjects;
}

template <typename GameObjectType>
inline std::set<GameObjectType*> GameObjectManager::getAll() {
    std::set<GameObjectType*> gameObjects;
    for (auto& nameGameObjectPtrPair : nameToGameObjectPtr) {
        if (typeid(*nameGameObjectPtrPair.second) == typeid(GameObjectType)) {
            gameObjects.insert(static_cast<GameObjectType*>(nameGameObjectPtrPair.second.get()));
        }
    }
    return gameObjects;
}

template <typename ComponentType>
inline std::set<ComponentType*> GameObjectManager::getAllComponents() {
    std::set<ComponentType*> components;
    for (auto& nameGameObjectPtrPair : nameToGameObjectPtr) {
        auto* collider = nameGameObjectPtrPair.second->getComponent<ComponentType>();
        if (collider) {
            components.insert(collider);
        }
    }
    return components;
}

}  // namespace engine
