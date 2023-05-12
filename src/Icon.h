//
// Created by NESco on 27/03/2022.
//

#ifndef PLATFORMERSFML_ICON_H
#define PLATFORMERSFML_ICON_H
#include <SFML/Graphics.hpp>

class Icon
{
 public:
  // constructon
  Icon();
  void Setup(std::string filename, int pos);

  //attributes
  sf::Sprite picture;
  sf::Texture icon_texture;
  bool alive = false;
  int relpos;  //the position of the icon relative to the screen- used for moving the icon with the view
};

#endif // PLATFORMERSFML_ICON_H
