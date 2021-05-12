#pragma once

#include <SFML/Graphics.hpp>

#include "gameobjectmanager.h"

class Game {
   public:
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const float FIXED_UPDATE_INTERVAL;
    static const float FPS_COUNTER_UPDATE_INTERVAL;
    static const float TOUCHING_TOLERANCE;

    static void start();

    static bool isUnderFloor(const sf::Rect<float>& boundingBox);
    static float amountUnderFloor(const sf::Rect<float>& boundingBox);
    static bool isOnFloor(const sf::Rect<float>& boundingBox);

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
