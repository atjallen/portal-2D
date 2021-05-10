#pragma once

#include <functional>
#include <map>
#include <memory>
#include <set>

#include "gameobject.h"

class GameObjectManager {
   public:
    GameObjectManager() = default;
    ~GameObjectManager() = default;

    template <typename GameObjectType>
    GameObjectType& create(const std::string& name);
    template <typename GameObjectType>
    GameObjectType& get(const std::string& name);
    void remove(const std::string& name);

    void drawAll(sf::RenderWindow& window);
    void updateAll(const sf::Time& frameTime);

   private:
    std::map<std::string, std::unique_ptr<GameObject>> nameToGameObjectPtr;
};

template <typename GameObjectType>
inline GameObjectType& GameObjectManager::create(const std::string& name) {
    static_assert(std::is_base_of<GameObject, GameObjectType>::value,
                  "Class not subclass of GameObject");
    nameToGameObjectPtr[name] = std::make_unique<GameObjectType>();
    return static_cast<GameObjectType&>(*nameToGameObjectPtr[name]);
}

template <typename GameObjectType>
inline GameObjectType& GameObjectManager::get(const std::string& name) {
    return static_cast<GameObjectType&>(nameToGameObjectPtr.at(name));
}

