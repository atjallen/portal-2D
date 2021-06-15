#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>

#include "gameobjectmanager.h"
#include "hitinfo.h"

#include "components/collision.h"

class Game {
   public:
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const float FIXED_UPDATE_INTERVAL;
    static const float FPS_COUNTER_UPDATE_INTERVAL;
    static const float TOUCHING_TOLERANCE;
    static const float RAYCAST_INTERVAL;
    static const float RAYCAST_MAX;

    static void start();

    static bool isOnFloor(GameObject& gameObject);

    static GameObject& getGameObject(const std::string& name);
    static std::set<Collision*> getAllCollisionComponents();

    static HitInfo raycast(const sf::Vector2f& position,
                           float angle,
                           const std::set<Collision*>& exclude = {});

    static sf::Vector2i getMousePosition();

   private:
    enum class GameState {
        Uninitialised,
        ShowingSplash,
        Paused,
        ShowingMenu,
        Playing,
        Exiting,
    };

    static GameState gameState;
    static sf::RenderWindow mainWindow;
    static GameObjectManager gameObjectManager;
    static sf::Clock updateClock;
    static sf::Clock fixedUpdateClock;
    static sf::Clock fpsClock;
    static int frameCounter;

    static sf::Font textFont;
    static sf::Text fpsCounter;

    static void gameLoop();

    static void showSplashScreen();
    static void showMenu();
};
