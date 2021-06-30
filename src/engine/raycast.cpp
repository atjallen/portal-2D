#include "raycast.h"

#include "engine.h"

#include "../util/container.h"

namespace raycast {

HitInfo raycast(const sf::Vector2f& position,
                float angle,
                const std::set<Collider*>& exclude) {
    sf::Vector2f rayDirection(std::cos(angle), std::sin(angle));
    std::set<Collider*> colliders;
    for (auto* colliderPtr : Engine::getAllComponents<Collider>()) {
        if (!util::containsFast(exclude, colliderPtr)) {
            colliders.insert(colliderPtr);
        }
    }

    // Simple raycasting algorithm
    // Basically advance along the ray by a fixed interval until you reach a
    // collider or the max distance
    sf::Vector2f checkPosition = position;
    float distance = 0;
    while (distance < RAYCAST_MAX) {
        for (auto* colliderPtr : colliders) {
            if (colliderPtr->getBoundingBox().contains(checkPosition)) {
                return {true, checkPosition, colliderPtr};
            }
        }

        distance += RAYCAST_INTERVAL;
        checkPosition += rayDirection * RAYCAST_INTERVAL;
    }

    return {false, sf::Vector2f(), nullptr};
}

}  // namespace raycast
