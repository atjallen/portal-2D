#pragma once

#include <SFML/System.hpp>

#include "components/collision.h"

struct HitInfo {
    bool hit;
    sf::Vector2f hitPosition;
    Collision* collision;
};
