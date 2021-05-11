#pragma once

#include <SFML/Graphics.hpp>

#include "gameobjectmanager.h"

class Game {
   public:
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const float FIXED_UPDATE_INTERVAL;

    static void start();

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

    static void gameLoop();

    static void showSplashScreen();
    static void showMenu();
};
