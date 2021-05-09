#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

class MainMenu {
   public:
    enum class MenuResult { Nothing, Exit, Play };

    struct MenuItem {
        sf::Rect<int> rect;
        MenuResult action;
    };

    MenuResult show(sf::RenderWindow& window);

   private:
    MenuResult getMenuResponse(sf::RenderWindow& window);
    MenuResult handleClick(int x, int y);
    std::vector<MenuItem> menuItems;
};
