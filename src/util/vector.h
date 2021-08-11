#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <array>
#include <cmath>
#include <iostream>
#include <tuple>

#include <SFML/Graphics.hpp>

namespace util {

class Line {
   public:
    Line(const sf::Vector2f& origin, const sf::Vector2f& direction);
    Line(const sf::Vector2f& origin, float angle);

    std::tuple<bool, sf::Vector2f> intersect(const Line& other) const;

    sf::Vector2f getOrigin() const;
    sf::Vector2f getDirection() const;

   protected:
    std::tuple<bool, float> calculateIntersectionDistance(
        const Line& other) const;

    virtual bool validate(float id) const;

   private:
    sf::Vector2f origin;
    sf::Vector2f direction;
};

class Ray : public Line {
    using Line::Line;

   protected:
    virtual bool validate(float id) const;
};

class LineSegment : public Line {
   public:
    LineSegment(const sf::Vector2f& origin,
                const sf::Vector2f& direction,
                float length);
    LineSegment(const sf::Vector2f& origin, float angle, float length);

    float getLength() const;

   protected:
    virtual bool validate(float id) const;

   private:
    float length;
};

template <typename T>
float length(const sf::Vector2<T>& a) {
    return std::sqrt(a.x * a.x + a.y * a.y);
}

template <typename T>
sf::Vector2<T> normalize(const sf::Vector2<T>& a) {
    return a / length(a);
}

template <typename T>
float dot(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return a.x * b.x + a.y * b.y;
};

template <typename T>
float angleBetween(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return std::atan2(b.y, b.x) - std::atan2(a.y, a.x);
}

template <typename T>
float radToDeg(T rads) {
    return rads * 180 / M_PI;
}

template <typename T>
float degToRad(T degs) {
    return degs * M_PI / 180;
}

template <typename T>
sf::Vector2<T> angleToVector(T angle) {
    return sf::Vector2<T>(std::cos(angle), std::sin(angle));
}

template <typename T>
float vectorToAngle(const sf::Vector2<T>& vector) {
    return std::atan2(vector.y, vector.x);
}

template <typename T>
std::array<sf::Vector2<T>, 4> rectToPoints(const sf::Rect<T>& rect) {
    return {sf::Vector2<T>(rect.left, rect.top),
            sf::Vector2<T>(rect.left + rect.width, rect.top),
            sf::Vector2<T>(rect.left + rect.width, rect.top + rect.height),
            sf::Vector2<T>(rect.left, rect.top + rect.height)};
}

}  // namespace util
