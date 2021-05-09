#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
    static const int WINDOW_WIDTH = 1920;
    static const int WINDOW_HEIGHT = 1080;

    static void start();

private:
    enum class GameState
    {
        Uninitialised,
        ShowingSplash,
        Paused,
        ShowingMenu,
        Playing,
        Exiting,
    };

    static GameState gameState;
    static sf::RenderWindow mainWindow;

    static void gameLoop();

    static void showSplashScreen();
    static void showMenu();
};
