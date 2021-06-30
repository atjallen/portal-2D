#include "engine.h"

#include <cmath>
#include <iostream>
#include <set>
#include <string>

#include <SFML/Graphics.hpp>

#include "config.h"
#include "gameobject.h"

#include "../util/container.h"

const int Engine::WINDOW_WIDTH = 1920;
const int Engine::WINDOW_HEIGHT = 1080;
const float Engine::FIXED_UPDATE_INTERVAL = 0.02f;
const float Engine::FPS_COUNTER_UPDATE_INTERVAL = 0.1f;
const float Engine::FPS_COUNTER_SMOOTHING = 0.9f;

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
    // Main loop
    while (true) {
        // Clear window
        mainWindow.clear(sf::Color(0, 0, 0));

        // Update fps
        fps = (fps * FPS_COUNTER_SMOOTHING) +
              (1.0f / updateClock.getElapsedTime().asSeconds() *
               (1.0f - FPS_COUNTER_SMOOTHING));

        // Update and draw fps counter
        if (fpsClock.getElapsedTime().asSeconds() >
            FPS_COUNTER_UPDATE_INTERVAL) {
            fpsClock.restart();
            fpsCounter.setString("FPS: " + std::to_string(fps));
        }
        mainWindow.draw(fpsCounter);

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
                break;
            }
        }
    }

    mainWindow.close();
}

sf::Vector2i Engine::getMousePosition() {
    return sf::Mouse::getPosition(mainWindow);
}
