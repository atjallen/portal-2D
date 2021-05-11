#pragma once

#include <SFML/Graphics.hpp>

class GameObject;

class Component {
   public:
    Component(GameObject& gameObject);
    virtual ~Component() = default;

    virtual void draw(sf::RenderWindow& window);
    virtual void update(const sf::Time& frameTime);
    virtual void fixedUpdate(const sf::Time& frameTime);

   protected:
    GameObject& gameObject;
};
