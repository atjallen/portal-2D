#pragma once

#include <SFML/Graphics.hpp>

#include "engine/components/component.h"
#include "engine/components/transform.h"

namespace engine {

class Sprite : public Component {
   public:
    Sprite(GameObject& gameObject);
    Sprite(GameObject& gameObject, const std::string& filename);
    Sprite(GameObject& gameObject, const std::string& filename, const sf::Vector2f& dimensions);
    virtual ~Sprite() = default;

    virtual void draw(sf::RenderWindow& window);

    sf::Texture& getTexture();
    sf::Sprite& getSprite();

    void setDimensions(const sf::Vector2f& dimensions);

    void loadTexture(const std::string& filename);

   private:
    bool loaded;
    std::string filename;
    sf::Texture texture;
    sf::Sprite sprite;

    Transform& transform;

    void resetOrigin();
};

}  // namespace engine
