//
// Created by NESco on 23/03/2022.
//

#ifndef PLATFORMERSFML_SOLIDS_H
#define PLATFORMERSFML_SOLIDS_H
#include <SFML/Graphics.hpp>

class Solids
{
 public:
  //construction
  Solids();
  void Setup(std::string filename);

  //attributes
  sf::Texture solid_texture;
  sf::Sprite form;
};

#endif // PLATFORMERSFML_SOLIDS_H
