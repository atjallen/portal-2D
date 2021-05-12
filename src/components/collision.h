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
    void setBoundingBox(const sf::Rect<float>& boundingBox);

   private:
    sf::Rect<float> boundingBox;

    Transform& transform;
    Physics& physics;
};
