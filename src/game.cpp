#include "game.h"

#include "splash.h"
#include "mainmenu.h"

void Game::start()
{
    if (gameState != GameState::Uninitialised)
    {
        return;
    }

    mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Portal 2D");

    gameState = GameState::Playing;

    gameLoop();

    mainWindow.close();
}

void Game::gameLoop()
{
    sf::Event event;
    while (true)
    {
        if (mainWindow.pollEvent(event))
        {
            switch (gameState)
            {
            case GameState::ShowingSplash:
            {
                showSplashScreen();
                break;
            }

            case GameState::ShowingMenu:
            {
                showMenu();
                break;
            }

            case GameState::Playing:
            {
                mainWindow.clear(sf::Color(0, 0, 0));
                //gameObjectManager.drawAll(mainWindow);
                mainWindow.display();

                if (event.type == sf::Event::Closed)
                {
                    gameState = GameState::Exiting;
                }

                if (
                    event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape
                    )
                {
                    showMenu();
                }

                break;
            }

            case GameState::Exiting:
            {
                return;
            }
            }
        }
    }
}

void Game::showSplashScreen()
{
    SplashScreen splashScreen;
    splashScreen.show(mainWindow);
    gameState = GameState::ShowingMenu;
}

void Game::showMenu()
{
    MainMenu mainMenu;
    MainMenu::MenuResult result = mainMenu.show(mainWindow);

    switch (result)
    {
    case MainMenu::MenuResult::Exit:
    {
        gameState = GameState::Exiting;
        break;
    }

    case MainMenu::MenuResult::Play:
    {
        gameState = GameState::Playing;
        break;
    }
    }
}

Game::GameState Game::gameState = GameState::Uninitialised;
sf::RenderWindow Game::mainWindow;
