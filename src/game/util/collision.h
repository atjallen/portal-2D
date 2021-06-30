#pragma once

#include "../../engine/components/collider.h"
#include "../../engine/engine.h"

#include "../gameobjects/floor.h"

namespace gameutil {

bool isOnFloor(GameObject& gameObject) {
    auto& gameObjectCollider = *gameObject.getComponent<Collider>();
    auto floors = Engine::getAllGameObjects<Floor>();
    for (auto* floorPtr : floors) {
        auto* floorCollider = floorPtr->getComponent<Collider>();
        if (gameObjectCollider.isTouchingBelow(*floorCollider)) {
            return true;
        }
    }
    return false;
}

}  // namespace gameutil
