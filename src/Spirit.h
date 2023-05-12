//
// Created by NESco on 22/04/2022.
//

#ifndef PLATFORMERSFML_SPIRIT_H
#define PLATFORMERSFML_SPIRIT_H

#include "Creature.h"

class Spirit: public Creature
{
 public:
  //construction
  Spirit();
  void Setup();

  //methods
  void Drop();

};

#endif // PLATFORMERSFML_SPIRIT_H
