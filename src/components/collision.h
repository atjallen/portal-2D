#pragma once

#include "component.h"
#include "transform.h"
#include "physics.h"

class Collision : public Component {
   public:
    Collision(GameObject& gameObject);
    virtual ~Collision() = default;

    virtual void update(const sf::Time& frameTime);
    virtual void fixedUpdate(const sf::Time& frameTime);

    sf::Rect<float> getBoundingBox() const;
    void setBoundingBoxDimensions(const sf::Vector2f& dimensions);
    void setKinematic(bool kinematic);

   private:
    sf::Rect<float> boundingBox;
    bool kinematic;

    Transform& transform;
    Physics& physics;
};
