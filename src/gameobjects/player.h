#pragma once

#include "gameobject.h"

class Player : public GameObject {
   public:
    Player();
    ~Player() = default;

    virtual void update(const sf::Time& frameTime);

   //private:
   // float velocity;
   // float maxVelocity;
   // float acceleration;
   // float drag;
};
