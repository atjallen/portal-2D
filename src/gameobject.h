#pragma once

#include <SFML/System.hpp>

class GameObject {
   public:
    GameObject() = default;
    virtual ~GameObject() = default;

    virtual void setPosition(const sf::Vector2f& position);
    virtual sf::Vector2f getPosition() const;
    virtual void move(const sf::Vector2f& moveBy);

    virtual void update(const sf::Time& elapsedTime) = 0;

   protected:
    sf::Vector2f position;
};