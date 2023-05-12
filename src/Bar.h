//
// Created by NESco on 27/04/2022.
//

#ifndef PLATFORMERSFML_BAR_H
#define PLATFORMERSFML_BAR_H

#include "Icon.h"

class Bar: public Icon
{
 public:
  // constructon
  Bar();
  void Setup(int pos);

  //methods
  void Fill(bool empty);

  //attributes
  int rectnum;  //the current position on the spritesheet, going down.
  sf::IntRect bar_rect;

};

#endif // PLATFORMERSFML_BAR_H
