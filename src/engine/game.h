#pragma once

#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>

#include "gameobjectmanager.h"
#include "hitinfo.h"

#include "components/collider.h"

class Game {
   public:
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const float FIXED_UPDATE_INTERVAL;
    static const float FPS_COUNTER_UPDATE_INTERVAL;
    static const float FPS_COUNTER_SMOOTHING;
    static const float TOUCHING_TOLERANCE;
    static const float RAYCAST_INTERVAL;
    static const float RAYCAST_MAX;

    static void initialise();
    static void run();

    static std::set<Collider*> getAllColliderComponents();

    template <typename GameObjectType = GameObject>
    static GameObjectType& get(const std::string& name);

    template <typename GameObjectType>
    static std::set<GameObjectType*> getAll();

    template <typename GameObjectType = GameObject>
    static GameObjectType& create(const std::string& name);

    static HitInfo raycast(const sf::Vector2f& position,
                           float angle,
                           const std::set<Collider*>& exclude = {});

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

    static void gameLoop();
};

template <typename GameObjectType>
inline GameObjectType& Game::get(const std::string& name) {
    return gameObjectManager.get<GameObjectType>(name);
}

template <typename GameObjectType>
inline std::set<GameObjectType*> Game::getAll() {
    return gameObjectManager.getAll<GameObjectType>();
}

template <typename GameObjectType>
inline GameObjectType& Game::create(const std::string& name) {
    return gameObjectManager.create<GameObjectType>(name);
}
