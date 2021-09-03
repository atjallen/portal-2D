#pragma once

#include <array>
#include <cmath>

#include <SFML/Graphics.hpp>

namespace util {

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
std::array<sf::Vector2<T>, 4> rectToPoints(const sf::Rect<T>& rect) {
    return {sf::Vector2<T>(rect.left, rect.top), sf::Vector2<T>(rect.left + rect.width, rect.top),
            sf::Vector2<T>(rect.left + rect.width, rect.top + rect.height),
            sf::Vector2<T>(rect.left, rect.top + rect.height)};
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& vector) {
    return os << "(" << vector.x << ", " << vector.y << ")";
}

// Implemented for potential future use but as of now unused due to fears of memory overheads since sf::Vector2<T> is
// used a lot
template <typename T>
class Vector2 : public sf::Vector2<T> {
   public:
    using sf::Vector2<T>::Vector2;
    Vector2(const sf::Vector2<T>& parent);

    float length() const;
    Vector2<T> normalize() const;
    float dot(const Vector2<T>& other) const;
    float angleBetween(const Vector2<T>& other) const;
};

typedef Vector2<float> Vector2f;

template <typename T>
inline Vector2<T>::Vector2(const sf::Vector2<T>& parent) : sf::Vector2<T>(parent) {}

template <typename T>
inline float Vector2<T>::length() const {
    return util::length(*this);
}

template <typename T>
inline Vector2<T> Vector2<T>::normalize() const {
    return util::normalize(*this);
}

template <typename T>
inline float Vector2<T>::dot(const Vector2<T>& other) const {
    return util::dot(*this, other);
}

template <typename T>
inline float Vector2<T>::angleBetween(const Vector2<T>& other) const {
    return util::angleBetween(*this, other);
}

}  // namespace util
