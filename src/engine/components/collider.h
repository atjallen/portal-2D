#pragma once

#include "engine/component.h"

#include "engine/components/physics.h"
#include "engine/components/transform.h"

namespace engine {

class Collider : public Component {
   public:
    Collider(GameObject& gameObject);
    Collider(GameObject& gameObject, const sf::Vector2f& dimensions);
    virtual ~Collider() = default;

    virtual void fixedUpdate(const sf::Time& frameTime);

    sf::Rect<float> getBoundingBox() const;
    void setBoundingBoxDimensions(const sf::Vector2f& dimensions);
    void setKinematic(bool kinematic);

    bool isColliding(const Collider& other);
    bool isTouchingBelow(const Collider& other);

   private:
    float boundingBoxWidth;
    float boundingBoxHeight;
    bool kinematic;

    Transform& transform;
    Physics& physics;
};

}  // namespace engine
