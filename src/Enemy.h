//
// Created by NESco on 23/03/2022.
//

#ifndef PLATFORMERSFML_ENEMY_H
#define PLATFORMERSFML_ENEMY_H

#include "Creature.h"

class Enemy: public Creature
{
 public:
  //construction
  Enemy();
  void Setup(int X, int Y);

  //methods
  void Move();
  int PlayerCollision(sf::Sprite player);
  void Animate();

  //attributes
  bool left;  //whether the enemy is going left or right
  bool right;
  float enemyspeed = 0.25;  //the enemy's walking speed
  int leftbound;  //the left and right bounds of their movement
  int rightbound;

};

#endif // PLATFORMERSFML_ENEMY_H
