//
// Created by NESco on 23/03/2022.
//

#include "Solids.h"
#include <iostream>

Solids::Solids()
{
}

void Solids::Setup(std::string filename)  //sets up the texture for the solid
{
  if (!solid_texture.loadFromFile(filename))  //loads the laser image into the game
  {
    std::cout << "platform texture didn't load \n";  //checks if the image loaded correctly
  }
  form.setTexture(solid_texture);
}