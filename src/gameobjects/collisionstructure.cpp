#include "collisionstructure.h"

CollisionStructure::CollisionStructure()
    : collision(createComponent<Collision>()) {
    collision.setKinematic(true);
}

void CollisionStructure::setDimensions(const sf::Vector2f& dimensions) {
    Structure::setDimensions(dimensions);
    collision.setBoundingBoxDimensions(dimensions);
}
