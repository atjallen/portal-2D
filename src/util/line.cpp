#include "line.h"

#include <tuple>

#include "util/units.h"
#include "util/vector.h"

namespace util {

Line::Line(const sf::Vector2f& origin, const sf::Vector2f& direction)
    : origin(origin), direction(util::normalize(direction)) {}

Line::Line(const sf::Vector2f& origin, float angle) : Line(origin, angleToVector(angle)) {}

std::tuple<bool, sf::Vector2f> Line::intersect(const Line& other) const {
    bool intersects;
    float thisID, otherID;
    std::tie(intersects, thisID) = this->calculateIntersectionDistance(other);
    std::tie(std::ignore, otherID) = other.calculateIntersectionDistance(*this);

    // If the lines do not intersect, or validation fails for either line (e.g.
    // one is a ray/line segment and the intersection point lies on the other
    // side of the ray/outside of the line segment) then there is no
    // intersection
    if (!intersects || !this->validate(thisID) || !other.validate(otherID)) {
        return std::make_tuple(false, sf::Vector2f());
    }

    return std::make_tuple(true, this->origin + thisID * this->direction);
}

sf::Vector2f Line::getOrigin() const {
    return origin;
}

sf::Vector2f Line::getDirection() const {
    return direction;
}

// Calculate the intersection distance (the value of the variable in the vector
// equation of the line at which point the line equation resolves to the
// intersection point) between this and another line
// i.e. if the two lines are defined by
//   this = (x1, y1) + a(u1, v1)
//   other = (x2, y2) + b(u2, v2)
// then the intersection distance is the value of a at the point at which the
// two lines intersect
std::tuple<bool, float> Line::calculateIntersectionDistance(const Line& other) const {
    float x1 = this->origin.x, y1 = this->origin.y, u1 = this->direction.x, v1 = this->direction.y;
    float x2 = other.origin.x, y2 = other.origin.y, u2 = other.direction.x, v2 = other.direction.y;

    // By my calculations, the intersection distance of the two lines defined as
    // above is
    //     u2(y2 - y1) + v2(x1 - x2)
    // a = -------------------------
    //            u2v1 - u1v2
    float denominator = u2 * v1 - u1 * v2;

    // If the denominator is 0, the lines are parallel and do not intersect
    if (denominator == 0) {
        return std::make_tuple(false, 0);
    }

    float a = (u2 * (y2 - y1) + v2 * (x1 - x2)) / denominator;
    return std::make_tuple(true, a);
}

// The intersection distance is always valid for a line (since intersection was
// checked during the calculation of the intersection distance)
bool Line::validate(float id) const {
    return true;
}

// The intersection distance is valid for a ray only if it is on the 'positive'
// side of the ray
bool Ray::validate(float id) const {
    return Line::validate(id) && id >= 0;
}

LineSegment::LineSegment(const sf::Vector2f& origin, const sf::Vector2f& direction, float length)
    : Line(origin, direction), length(length) {}

LineSegment::LineSegment(const sf::Vector2f& origin, float angle, float length) : Line(origin, angle), length(length) {}

float LineSegment::getLength() const {
    return length;
}

// The intersection distance is valid for a line segment only if it lies in the
// length of the line segment
bool LineSegment::validate(float id) const {
    return Line::validate(id) && id >= 0 && id < length;
}

}  // namespace util
