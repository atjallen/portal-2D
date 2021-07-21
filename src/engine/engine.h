#pragma once

#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>

#include "gameobjectmanager.h"

#include "components/collider.h"

namespace engine {

class Engine {
   public:
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const float FIXED_UPDATE_INTERVAL;
    static const float FPS_COUNTER_UPDATE_INTERVAL;
    static const float FPS_COUNTER_SMOOTHING;

    static void initialise();
    static void run();

    template <typename GameObjectType = GameObject>
    static GameObjectType& getGameObject(const std::string& name);

    template <typename GameObjectType>
    static std::set<GameObjectType*> getAllGameObjects();

    template <typename GameObjectType = GameObject>
    static GameObjectType& createGameObject(const std::string& name);

    template <typename ComponentType>
    static std::set<ComponentType*> getAllComponents();

    static sf::Vector2i getMousePosition();

   private:
    static sf::RenderWindow mainWindow;
    static GameObjectManager gameObjectManager;
    static sf::Clock updateClock;
    static sf::Clock fixedUpdateClock;
    static sf::Clock fpsClock;
    static int fps;

    static sf::Font textFont;
    static sf::Text fpsCounter;
};

template <typename GameObjectType>
inline GameObjectType& Engine::getGameObject(const std::string& name) {
    return gameObjectManager.get<GameObjectType>(name);
}

template <typename GameObjectType>
inline std::set<GameObjectType*> Engine::getAllGameObjects() {
    return gameObjectManager.getAll<GameObjectType>();
}

template <typename GameObjectType>
inline GameObjectType& Engine::createGameObject(const std::string& name) {
    return gameObjectManager.create<GameObjectType>(name);
}

template <typename ComponentType>
inline std::set<ComponentType*> Engine::getAllComponents() {
    return gameObjectManager.getAllComponents<ComponentType>();
}

}  // namespace engine
