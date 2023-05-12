//
// Created by NESco on 23/03/2022.
//

#ifndef PLATFORMERSFML_CREATURE_H
#define PLATFORMERSFML_CREATURE_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Creature
{
 public:
  //construction
  Creature();
  void Setup(std::string filename, int animmax);

  //methods
  void Move(bool right, bool left, float speed);
  bool Collision(sf::Sprite other);
  int Grounded(sf::Sprite platform);
  bool Animate(float rate);


  //attributes
  sf::Texture creature_texture;
  sf::Sprite body;
  sf::IntRect creature_rect;
  bool alive;  //whether the creature will show up and interact with things or not
  bool ground;  //whether the creature is touching the ground
  float groundlevel;  //sets the level of the ground, to apply to the creature, so they don't fall further
  float x;  //current x position
  float y;  //and y
  bool anim;  //whether the creature is animated or not
  float rectnum;  //current position on the spritesheet
  int rectmax;  //number of sprites on the sheet


};

#endif // PLATFORMERSFML_CREATURE_H
