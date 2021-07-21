#pragma once

#include "../../engine/gameobject.h"

#include "../../engine/components/transform.h"

class PortalGun : public engine::GameObject {
   public:
    PortalGun();
    virtual ~PortalGun() = default;

    virtual void draw(sf::RenderWindow& window);

   private:
    engine::Transform& transform;
};
