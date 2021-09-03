#pragma once

#include <SFML/System.hpp>

namespace util {

class Line {
   public:
    Line(const sf::Vector2f& origin, const sf::Vector2f& direction);
    Line(const sf::Vector2f& origin, float angle);

    std::tuple<bool, sf::Vector2f> intersect(const Line& other) const;

    sf::Vector2f getOrigin() const;
    sf::Vector2f getDirection() const;

   protected:
    std::tuple<bool, float> calculateIntersectionDistance(const Line& other) const;

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
    LineSegment(const sf::Vector2f& origin, const sf::Vector2f& direction, float length);
    LineSegment(const sf::Vector2f& origin, float angle, float length);

    float getLength() const;

   protected:
    virtual bool validate(float id) const;

   private:
    float length;
};

}  // namespace util
