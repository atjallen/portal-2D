#include "game.h"

#include "mainmenu.h"
#include "splash.h"

#include "player.h"

#include "transform.h"

void Game::start() {
    if (gameState != GameState::Uninitialised) {
        return;
    }

    mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32),
                      "Portal 2D");

    auto& player = gameObjectManager.create<Player>("Player");
    player.getComponent<Transform>()->setPosition(
        sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

    gameState = GameState::Playing;

    gameLoop();

    mainWindow.close();
}

void Game::gameLoop() {
    while (true) {
        switch (gameState) {
            case GameState::ShowingSplash: {
                showSplashScreen();
                break;
            }

            case GameState::ShowingMenu: {
                showMenu();
                break;
            }

            case GameState::Playing: {
                mainWindow.clear(sf::Color(0, 0, 0));
                gameObjectManager.updateAll(frameTimeClock.restart());
                gameObjectManager.drawAll(mainWindow);
                mainWindow.display();

                sf::Event event;
                if (mainWindow.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        gameState = GameState::Exiting;
                    }

                    if (event.type == sf::Event::KeyPressed &&
                        event.key.code == sf::Keyboard::Escape) {
                        showMenu();
                    }
                }

                break;
            }

            case GameState::Exiting: {
                return;
            }
        }
    }
}

void Game::showSplashScreen() {
    SplashScreen splashScreen;
    splashScreen.show(mainWindow);
    gameState = GameState::ShowingMenu;
}

void Game::showMenu() {
    MainMenu mainMenu;
    MainMenu::MenuResult result = mainMenu.show(mainWindow);

    switch (result) {
        case MainMenu::MenuResult::Exit: {
            gameState = GameState::Exiting;
            break;
        }

        case MainMenu::MenuResult::Play: {
            gameState = GameState::Playing;
            break;
        }
    }
}

Game::GameState Game::gameState = GameState::Uninitialised;
sf::RenderWindow Game::mainWindow;
GameObjectManager Game::gameObjectManager;
sf::Clock Game::frameTimeClock;
