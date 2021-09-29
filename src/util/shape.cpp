#include "shape.h"

#include <algorithm>
#include <tuple>

#include "util/vector.h"

namespace util {

std::vector<sf::Vector2f> util::getPointsTransformed(const sf::ConvexShape& shape) {
    std::vector<sf::Vector2f> points;
    for (int i = 0; i < shape.getPointCount(); i++) {
        points.push_back(shape.getTransform().transformPoint(shape.getPoint(i)));
    }
    return points;
}

std::vector<sf::Vector2f> util::getEdges(const sf::ConvexShape& shape) {
    auto points = getPointsTransformed(shape);
    std::vector<sf::Vector2f> edges;
    for (int i = 0; i < points.size() - 1; i++) {
        edges.push_back(points[i + 1] - points[i]);
    }
    return edges;
}

bool util::doesIntersect(const sf::ConvexShape& shape1, const sf::ConvexShape& shape2) {
    auto shape1Points = getPointsTransformed(shape1);
    auto shape2Points = getPointsTransformed(shape2);
    auto shape1Edges = getEdges(shape1);
    auto shape2Edges = getEdges(shape2);
    // TODO: Make this better?
    auto allEdges = shape1Edges;
    allEdges.insert(allEdges.end(), shape2Edges.begin(), shape2Edges.end());

    // See http://web.archive.org/web/20141127210836/http://content.gpwiki.org/index.php/Polygon_Collision
    for (auto& edge : allEdges) {
        auto getMinMaxProjections = [](const auto& perp, const auto& points) {
            float minProjection = dot(perp, points[0]);
            float maxProjection = minProjection;
            for (int i = 1; i < points.size(); i++) {
                float projection = dot(perp, points[i]);
                if (projection < minProjection) {
                    minProjection = projection;
                }
                if (projection > maxProjection) {
                    maxProjection = projection;
                }
            }
            return std::make_tuple(minProjection, maxProjection);
        };

        auto perp = util::normalize(sf::Vector2f(-edge.y, edge.x));

        float min1, max1, min2, max2;
        std::tie(min1, max1) = getMinMaxProjections(perp, shape1Points);
        std::tie(min2, max2) = getMinMaxProjections(perp, shape2Points);
        if (min1 > max2 || max1 < min2) {
            return false;
        }
    }

    return true;
}

}  // namespace util
