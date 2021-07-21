#pragma once

#include "../../engine/components/collider.h"
#include "../../engine/engine.h"

#include "../gameobjects/floor.h"

namespace gameutil {

bool isOnFloor(engine::GameObject& gameObject) {
    auto& gameObjectCollider = *gameObject.getComponent<engine::Collider>();
    auto floors = engine::Engine::getAllGameObjects<Floor>();
    for (auto* floorPtr : floors) {
        auto* floorCollider = floorPtr->getComponent<engine::Collider>();
        if (gameObjectCollider.isTouchingBelow(*floorCollider)) {
            return true;
        }
    }
    return false;
}

}  // namespace gameutil
