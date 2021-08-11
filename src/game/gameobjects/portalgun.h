#pragma once

#include "../../engine/gameobject.h"
#include "../../engine/raycast.h"

#include "../../engine/components/transform.h"

class PortalGun : public engine::GameObject {
   public:
    PortalGun();
    virtual ~PortalGun() = default;

    virtual void draw(sf::RenderWindow& window);

    void firePortalA();
    void firePortalB();

   private:
    engine::Transform& transform;

    void firePortal(const std::string& name, const sf::Color& color);
    engine::raycast::HitInfo raycast();
};
