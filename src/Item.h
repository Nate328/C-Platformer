//
// Created by NESco on 23/03/2022.
//

#ifndef PLATFORMERSFML_ITEM_H
#define PLATFORMERSFML_ITEM_H

#include "Solids.h"

class Item : public Solids
{
 public:
  //construction
  Item();
  void Setup(std::string filename);

  //methods
  bool Collision(sf::Sprite other);
  void Animate();

  //attributes
  bool alive;
  char type;  //whether it is a key or a coin
  float rectpos;  //current position of the spritesheet, going up
  int rectmax;  //how many sprites are on the sheet
  sf::IntRect item_rect;
  bool goingup;  //determines if the coin is floating up or down
};

#endif // PLATFORMERSFML_ITEM_H
