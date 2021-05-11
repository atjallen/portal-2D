#pragma once

#include <SFML/Graphics.hpp>

#include "component.h"
#include "transform.h"

class Sprite : public Component {
   public:
    Sprite(GameObject& gameObject);
    Sprite(GameObject& gameObject, const std::string& filename);
    virtual ~Sprite() = default;

    virtual void draw(sf::RenderWindow& window);
    virtual void update(const sf::Time& frameTime);

    void loadTexture(const std::string& filename);

    sf::Rect<float> getBoundingBox() const;

   private:
    bool loaded;
    sf::Sprite sprite;
    sf::Texture texture;
    std::string filename;

    Transform& transform;
};
