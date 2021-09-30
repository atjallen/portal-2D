#include "collider.h"

#include "engine/config.h"
#include "engine/engine.h"
#include "engine/gameobject.h"

#include "util/errors.h"
#include "util/shape.h"
#include "util/vertex.h"

namespace engine {

Collider::Collider(GameObject& gameObject)
    : Component(gameObject),
      kinematic(false),
      transform(*gameObject.getComponent<Transform>()),
      physics(*gameObject.getComponent<Physics>()) {}

void Collider::setKinematic(bool kinematic) {
    this->kinematic = kinematic;
}

void Collider::draw(sf::RenderWindow& window) {
    if (Config::getDebugFlag("drawColliders")) {
        auto points = getPoints();
        points.push_back(points[0]);
        window.draw(util::toVertexArray(points, sf::PrimitiveType::LineStrip, points.size()));
    }
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

bool Collider::isColliding(const Collider& other) {
    throw util::NotImplementedError();
}

bool Collider::isTouchingBelow(const Collider& other) {
    throw util::NotImplementedError();
}

void Collider::handleCollision(const Collider& other) {
    // Do nothing
}

}  // namespace engine
