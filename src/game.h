#pragma once

#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>

#include "gameobjectmanager.h"

#include "components/collision.h"

class Game {
   public:
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const float FIXED_UPDATE_INTERVAL;
    static const float FPS_COUNTER_UPDATE_INTERVAL;
    static const float TOUCHING_TOLERANCE;

    static void start();

    static bool isOnFloor(GameObject& gameObject);

    static std::vector<std::reference_wrapper<Collision>>
    getAllCollisionComponents();

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
