#pragma once

#include "visiblegameobject.h"

class Player : public VisibleGameObject {
   public:
    Player();
    ~Player() = default;

    void update(const sf::Time& frameTime);

   private:
    float velocity;
    float maxVelocity;
    float acceleration;
    float drag;
};
