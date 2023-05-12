//
// Created by NESco on 26/04/2022.
//

#ifndef PLATFORMERSFML_DOOR_H
#define PLATFORMERSFML_DOOR_H

#include "Solids.h"

class Door: public Solids
{
 public:
  //construction
  Door();
  void Setup();

  //attributes
  sf::IntRect door_rect;
  bool alive;

};

#endif // PLATFORMERSFML_DOOR_H
