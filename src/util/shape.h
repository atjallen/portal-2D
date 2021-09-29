#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

namespace util {

std::vector<sf::Vector2f> getPointsTransformed(const sf::ConvexShape& shape);
std::vector<sf::Vector2f> getEdges(const sf::ConvexShape& shape);

bool doesIntersect(const sf::ConvexShape& shape1, const sf::ConvexShape& shape2);

}  // namespace util
