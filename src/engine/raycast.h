#pragma once

#include <set>
#include <tuple>

#include <SFML/System.hpp>

#include "engine/components/collider.h"

#include "util/vector.h"

namespace engine {

namespace raycast {

struct HitInfo {
    bool hit;
    sf::Vector2f hitPosition;
    Collider* collider;
    util::LineSegment segment;

    HitInfo();
    HitInfo(bool hit, const sf::Vector2f& hitPosition, Collider* collider, const util::LineSegment& segment);
};

const float RAYCAST_INTERVAL = 10.0f;
const float RAYCAST_MAX = 10000;

HitInfo raycast(const sf::Vector2f& position, float angle, const std::set<Collider*>& exclude = {});

HitInfo raycast(const util::Ray& ray, const std::set<Collider*>& exclude = {});

}  // namespace raycast

}  // namespace engine
