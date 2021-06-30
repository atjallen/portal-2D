#pragma once

#include <SFML/System.hpp>

#include "components/collider.h"

struct HitInfo {
    bool hit;
    sf::Vector2f hitPosition;
    Collider* collider;
};
