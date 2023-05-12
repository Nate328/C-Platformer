//
// Created by NESco on 27/03/2022.
//

#include "Icon.h"
#include <iostream>

Icon::Icon()
{
}

void Icon::Setup(std::string filename, int pos) //sets up the icon and its relative position
{
  if (!icon_texture.loadFromFile(filename))  //loads the icon image into the game
  {
    std::cout << "health texture didn't load \n";  //checks if the image loaded correctly
  }
  picture.setTexture(icon_texture);
  alive = false;
  relpos = pos;
}