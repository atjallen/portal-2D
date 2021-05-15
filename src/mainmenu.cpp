#include "mainmenu.h"

#include <iostream>

#include "config.h"

MainMenu::MenuResult MainMenu::show(sf::RenderWindow& window) {
    // Load menu image from file
    sf::Texture mainMenuTx;
    mainMenuTx.loadFromFile(Config::getImageFilename("MainMenu"));
    sf::Sprite mainMenuSpr(mainMenuTx);

    // Setup clickable regions

    // Play menu item coordinates
    MenuItem playButton;
    playButton.rect.left = 780;
    playButton.rect.top = 400;
    playButton.rect.width = 360;
    playButton.rect.height = 130;
    playButton.action = MenuResult::Play;

    // Exit menu item coordinates
    MenuItem exitButton;
    exitButton.rect.left = 780;
    exitButton.rect.top = 520;
    exitButton.rect.width = 360;
    exitButton.rect.height = 120;
    exitButton.action = MenuResult::Exit;

    menuItems.push_back(playButton);
    menuItems.push_back(exitButton);

    window.draw(mainMenuSpr);
    window.display();

    return getMenuResponse(window);
}

MainMenu::MenuResult MainMenu::handleClick(int x, int y) {
    for (const auto& menuItem : menuItems) {
        if (menuItem.rect.contains(x, y)) {
            return menuItem.action;
        }
    }

    return MenuResult::Nothing;
}

MainMenu::MenuResult MainMenu::getMenuResponse(sf::RenderWindow& window) {
    sf::Event event;

    while (true) {
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                return handleClick(event.mouseButton.x, event.mouseButton.y);
            }

            if (event.type == sf::Event::Closed) {
                return MenuResult::Exit;
            }
        }
    }
}
