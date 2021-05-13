#pragma once

#include "component.h"
#include "transform.h"
#include "physics.h"

class Collision : public Component {
   public:
    Collision(GameObject& gameObject);
    virtual ~Collision() = default;

    virtual void fixedUpdate(const sf::Time& frameTime);

    sf::Rect<float> getBoundingBox() const;
    void setBoundingBoxDimensions(const sf::Vector2f& dimensions);
    void setKinematic(bool kinematic);

   private:
    float boundingBoxWidth;
    float boundingBoxHeight;
    bool kinematic;

    Transform& transform;
    Physics& physics;
};
