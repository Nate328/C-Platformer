//
// Created by NESco on 22/04/2022.
//

#include "Spirit.h"

Spirit::Spirit()
{}

void Spirit::Setup() //sets up the spirit
{
  Creature::Setup("Data/Images/player_splash.png", 0);
  alive = false;
}

void Spirit::Drop() //causes the spirit to fall if it's not on the ground
{
  if (!ground)
  {
    y += 5;
  }
}