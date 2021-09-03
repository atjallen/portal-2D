#include "raycast.h"

#include <algorithm>
#include <vector>

#include "engine.h"

#include "util/container.h"
#include "util/vector.h"

namespace engine {

namespace raycast {

HitInfo::HitInfo()
    : hit(false), hitPosition(sf::Vector2f()), collider(nullptr), segment(sf::Vector2f(), sf::Vector2f(), 0) {}

HitInfo::HitInfo(bool hit, const sf::Vector2f& hitPosition, Collider* collider, const util::LineSegment& segment)
    : hit(hit), hitPosition(hitPosition), collider(collider), segment(segment) {}

HitInfo raycast(const sf::Vector2f& position, float angle, const std::set<Collider*>& exclude) {
    return raycast(util::Ray(position, angle), exclude);
}

// Cast a ray in the scene and return whether it intersects with any colliders
// in the scene and if so return information about the collision. The raycasting
// works using vector arithmetic. Specifically, we consider all colliders in the
// scene and decompose those colliders into line segments. We try to intersect
// the ray with each line segment and store any hits. After checking all
// colliders, return the closest hit.
HitInfo raycast(const util::Ray& ray, const std::set<Collider*>& exclude) {
    std::vector<HitInfo> hits;
    for (auto* colliderPtr : Engine::getAllComponents<Collider>()) {
        if (!util::containsFast(exclude, colliderPtr)) {
            auto corners = util::rectToPoints(colliderPtr->getBoundingBox());
            for (int i = 0; i < 4; i++) {
                sf::Vector2f& segmentStart = corners[i];
                sf::Vector2f& segmentEnd = corners[(i + 1) % 4];
                sf::Vector2f segmentVector = segmentEnd - segmentStart;
                util::LineSegment segment(segmentStart, segmentVector, util::length(segmentVector));

                bool doesIntersect;
                sf::Vector2f intersectionPoint;
                std::tie(doesIntersect, intersectionPoint) = ray.intersect(segment);
                if (doesIntersect) {
                    hits.emplace_back(true, intersectionPoint, colliderPtr, segment);
                }
            }
        }
    }

    if (hits.empty()) {
        return HitInfo();
    }

    // Return the closest hit
    return *std::min_element(hits.begin(), hits.end(), [&](const auto& hitA, const auto& hitB) {
        return util::length(hitA.hitPosition - ray.getOrigin()) < util::length(hitB.hitPosition - ray.getOrigin());
    });
}

}  // namespace raycast

}  // namespace engine
