#include "collisionstructure.h"

#include "engine/components/boxcollider.h"

CollisionStructure::CollisionStructure(float width, float height, const sf::Vector2f& initialPosition)
    : Structure(width, height, initialPosition), collider(createComponent<engine::BoxCollider>(width, height)) {
    collider.setKinematic(true);
}
