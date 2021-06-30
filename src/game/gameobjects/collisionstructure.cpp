#include "collisionstructure.h"

CollisionStructure::CollisionStructure()
    : collider(createComponent<Collider>()) {
    collider.setKinematic(true);
}

void CollisionStructure::setDimensions(const sf::Vector2f& dimensions) {
    Structure::setDimensions(dimensions);
    collider.setBoundingBoxDimensions(dimensions);
}
