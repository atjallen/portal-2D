#pragma once

#include <SFML/Graphics.hpp>

#include "engine/config.h"

namespace engine {

class GameObject;  // Forward declaration to avoid circular import

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

}  // namespace engine
