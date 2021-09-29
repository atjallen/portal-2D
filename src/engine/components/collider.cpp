#include "collider.h"

#include "engine/engine.h"
#include "engine/gameobject.h"

#include "util/shape.h"

namespace engine {

Collider::Collider(GameObject& gameObject)
    : Component(gameObject),
      kinematic(false),
      transform(*gameObject.getComponent<Transform>()),
      physics(*gameObject.getComponent<Physics>()) {}

void Collider::setKinematic(bool kinematic) {
    this->kinematic = kinematic;
}

void Collider::fixedUpdate(const sf::Time& frameTime) {
    if (!kinematic) {
        for (auto* colliderPtr : Engine::getAllComponents<Collider>()) {
            if (colliderPtr != this) {
                handleCollision(*colliderPtr);
            }
        }
    }
}

}  // namespace engine
