#pragma once

#include <set>

#include <SFML/System.hpp>

#include "components/collider.h"

namespace raycast {

struct HitInfo {
    bool hit;
    sf::Vector2f hitPosition;
    Collider* collider;
};

const float RAYCAST_INTERVAL = 10.0f;
const float RAYCAST_MAX = 10000;

HitInfo raycast(const sf::Vector2f& position,
                float angle,
                const std::set<Collider*>& exclude = {});

}  // namespace raycast
