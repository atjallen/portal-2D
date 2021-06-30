#include "engine.h"

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

const int Engine::WINDOW_WIDTH = 1920;
const int Engine::WINDOW_HEIGHT = 1080;
const float Engine::FIXED_UPDATE_INTERVAL = 0.02f;
const float Engine::FPS_COUNTER_UPDATE_INTERVAL = 0.1f;
const float Engine::FPS_COUNTER_SMOOTHING = 0.9f;
const float Engine::TOUCHING_TOLERANCE = 10.0f;
const float Engine::RAYCAST_INTERVAL = 10.0f;
const float Engine::RAYCAST_MAX = 10000;

sf::RenderWindow Engine::mainWindow;
GameObjectManager Engine::gameObjectManager;
sf::Clock Engine::updateClock;
sf::Clock Engine::fixedUpdateClock;
sf::Clock Engine::fpsClock;
int Engine::fps = 0;

sf::Font Engine::textFont;
sf::Text Engine::fpsCounter;

void Engine::initialise() {
    textFont.loadFromFile(Config::getFontFilename("Arial"));
    fpsCounter.setFont(textFont);
    fpsCounter.setFillColor(sf::Color::White);
}

void Engine::run() {
    mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32),
                      "Portal 2D");
    mainLoop();
    mainWindow.close();
}

std::set<Collider*> Engine::getAllColliderComponents() {
    std::set<Collider*> colliders;
    for (auto* colliderPtr : gameObjectManager.getAll()) {
        auto* collider = colliderPtr->getComponent<Collider>();
        if (collider) {
            colliders.insert(collider);
        }
    }
    return colliders;
}

HitInfo Engine::raycast(const sf::Vector2f& position,
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

sf::Vector2i Engine::getMousePosition() {
    return sf::Mouse::getPosition(mainWindow);
}

void Engine::mainLoop() {
    while (true) {
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
            gameObjectManager.fixedUpdateAll(fixedUpdateClock.restart());
        }

        // Draw game objects
        gameObjectManager.drawAll(mainWindow);

        // Display window
        mainWindow.display();

        // Handle events
        sf::Event event;
        if (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return;
            }
        }
    }
}
