#include "game.h"

#include <cmath>
#include <string>

#include "mainmenu.h"
#include "splash.h"

#include "gameobjects/player.h"

#include "components/transform.h"

const int Game::WINDOW_WIDTH = 1920;
const int Game::WINDOW_HEIGHT = 1080;
const float Game::FIXED_UPDATE_INTERVAL = 0.02f;
const float Game::FPS_COUNTER_UPDATE_INTERVAL = 0.05f;
const float Game::TOUCHING_TOLERANCE = 10.0f;

Game::GameState Game::gameState = GameState::Uninitialised;
sf::RenderWindow Game::mainWindow;
GameObjectManager Game::gameObjectManager;
sf::Clock Game::updateClock;
sf::Clock Game::fixedUpdateClock;
sf::Clock Game::fpsClock;
int Game::frameCounter = 0;

sf::Font Game::textFont;
sf::Text Game::fpsCounter;

void Game::start() {
    if (gameState != GameState::Uninitialised) {
        return;
    }

    mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32),
                      "Portal 2D");

    textFont.loadFromFile("res/arial.ttf");

    fpsCounter.setFont(textFont);
    fpsCounter.setFillColor(sf::Color::White);

    auto& player = gameObjectManager.create<Player>("Player");
    player.getComponent<Transform>()->setPosition(
        sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

    gameState = GameState::Playing;

    gameLoop();

    mainWindow.close();
}

bool Game::isUnderFloor(const sf::Rect<float>& boundingBox) {
    return boundingBox.top + boundingBox.height >= WINDOW_HEIGHT;
}

float Game::amountUnderFloor(const sf::Rect<float>& boundingBox) {
    return (boundingBox.top + boundingBox.height) - WINDOW_HEIGHT;
}

bool Game::isOnFloor(const sf::Rect<float>& boundingBox) {
    return std::abs((boundingBox.top + boundingBox.height) - WINDOW_HEIGHT) <
           TOUCHING_TOLERANCE;
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

                // Display and/or update fps counter
                mainWindow.draw(fpsCounter);
                if (fpsClock.getElapsedTime().asSeconds() >
                    FPS_COUNTER_UPDATE_INTERVAL) {
                    fpsClock.restart();
                    fpsCounter.setString(
                        "FPS: " +
                        std::to_string(static_cast<int>(
                            frameCounter * (1 / FPS_COUNTER_UPDATE_INTERVAL))));
                    frameCounter = 0;
                }

                // Update game objects
                gameObjectManager.updateAll(updateClock.restart());

                // Fixed update game objects
                if (fixedUpdateClock.getElapsedTime().asSeconds() >
                    FIXED_UPDATE_INTERVAL) {
                    gameObjectManager.fixedUpdateAll(
                        fixedUpdateClock.restart());
                }

                // Draw game objects
                gameObjectManager.drawAll(mainWindow);

                // Display window
                mainWindow.display();

                // Handle events
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

                frameCounter++;

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
