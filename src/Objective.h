//
// Created by NESco on 22/04/2022.
//

#ifndef PLATFORMERSFML_OBJECTIVE_H
#define PLATFORMERSFML_OBJECTIVE_H

#include "Creature.h"

class Objective: public Creature
{
   public:
    //construction
    Objective();
    void Setup(bool real);

    //methods
    int PlayerCollision(sf::Sprite player);
    void Animate();

};

#endif // PLATFORMERSFML_OBJECTIVE_H
