#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "gameobject.h"

class VisibleGameObject : public GameObject {
   public:
    VisibleGameObject();
    virtual ~VisibleGameObject() = default;

    virtual void setPosition(const sf::Vector2f& position);
    virtual void move(const sf::Vector2f& moveBy);

    virtual void load(const std::string& filename);
    virtual void draw(sf::RenderWindow& window);

   protected:
    bool loaded;
    sf::Sprite sprite;
    sf::Texture texture;
    std::string filename;
};
