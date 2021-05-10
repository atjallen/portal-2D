#pragma once

#include <SFML/System.hpp>

#include "component.h"

class Transform : public Component {
   public:
    Transform(GameObject& gameObject);
    Transform(GameObject& gameObject, const sf::Vector2f& initPosition);
    virtual ~Transform() = default;

    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    void move(const sf::Vector2f& moveBy);

   private:
    sf::Vector2f position;
};
