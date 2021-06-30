#include "game.h"

#include <cmath>
#include <iostream>
#include <set>
#include <string>

#include <SFML/Graphics.hpp>

#include "config.h"
#include "gameobject.h"

#include "components/collider.h"
#include "components/sprite.h"
#include "components/transform.h"

#include "../util/container.h"

const int Game::WINDOW_WIDTH = 1920;
const int Game::WINDOW_HEIGHT = 1080;
const float Game::FIXED_UPDATE_INTERVAL = 0.02f;
const float Game::FPS_COUNTER_UPDATE_INTERVAL = 0.1f;
const float Game::FPS_COUNTER_SMOOTHING = 0.9f;
const float Game::TOUCHING_TOLERANCE = 10.0f;
const float Game::RAYCAST_INTERVAL = 10.0f;
const float Game::RAYCAST_MAX = 10000;

Game::GameState Game::gameState = GameState::Uninitialised;
sf::RenderWindow Game::mainWindow;
GameObjectManager Game::gameObjectManager;
sf::Clock Game::updateClock;
sf::Clock Game::fixedUpdateClock;
sf::Clock Game::fpsClock;
int Game::fps = 0;

sf::Font Game::textFont;
sf::Text Game::fpsCounter;

void Game::initialise() {
    if (gameState != GameState::Uninitialised) {
        return;
    }

    textFont.loadFromFile(Config::getFontFilename("Arial"));

    fpsCounter.setFont(textFont);
    fpsCounter.setFillColor(sf::Color::White);

    gameState = GameState::Playing;
}

void Game::run() {
    mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32),
                      "Portal 2D");
    gameLoop();
    mainWindow.close();
}

std::set<Collider*> Game::getAllColliderComponents() {
    std::set<Collider*> colliders;
    for (auto* colliderPtr : gameObjectManager.getAll()) {
        auto* collider = colliderPtr->getComponent<Collider>();
        if (collider) {
            colliders.insert(collider);
        }
    }
    return colliders;
}

HitInfo Game::raycast(const sf::Vector2f& position,
                      float angle,
                      const std::set<Collider*>& exclude) {
    sf::Vector2f rayDirection(std::cos(angle), std::sin(angle));
    std::set<Collider*> colliders;
    for (auto* colliderPtr : getAllColliderComponents()) {
        if (!util::containsFast(exclude, colliderPtr)) {
            colliders.insert(colliderPtr);
        }
    }

    // Simple raycasting algorithm
    // Basically advance along the ray by a fixed interval until you reach a
    // collider or the max distance
    sf::Vector2f checkPosition = position;
    float distance = 0;
    while (distance < RAYCAST_MAX) {
        for (auto* colliderPtr : colliders) {
            if (colliderPtr->getBoundingBox().contains(checkPosition)) {
                return {true, checkPosition, colliderPtr};
            }
        }

        distance += RAYCAST_INTERVAL;
        checkPosition += rayDirection * RAYCAST_INTERVAL;
    }

    return {false, sf::Vector2f(), nullptr};
}

sf::Vector2i Game::getMousePosition() {
    return sf::Mouse::getPosition(mainWindow);
}

void Game::gameLoop() {
    while (true) {
        switch (gameState) {
            case GameState::Playing: {
                mainWindow.clear(sf::Color(0, 0, 0));

                // Update fps
                fps = (fps * FPS_COUNTER_SMOOTHING) +
                      (1.0f / updateClock.getElapsedTime().asSeconds() *
                       (1.0f - FPS_COUNTER_SMOOTHING));

                // Display and update fps counter
                mainWindow.draw(fpsCounter);
                if (fpsClock.getElapsedTime().asSeconds() >
                    FPS_COUNTER_UPDATE_INTERVAL) {
                    fpsClock.restart();
                    fpsCounter.setString("FPS: " + std::to_string(fps));
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
                }

                break;
            }

            case GameState::Exiting: {
                return;
            }
        }
    }
}
