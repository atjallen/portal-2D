#pragma once

#include <SFML/Graphics.hpp>

#include "engine/components/component.h"

namespace engine {

class Transform : public Component, public sf::Transformable {
   public:
    Transform(GameObject& gameObject);
    virtual ~Transform() = default;

    void setPositionX(float x);
    void setPositionY(float y);

    float getRotationRads() const;
    void setRotationRads(float angle);
    void rotateRads(float angle);

    void lookAt(const sf::Vector2f& lookAtPosition);
};

}  // namespace engine
