//
// Created by NESco on 23/03/2022.
//

#ifndef PLATFORMERSFML_PLAYER_H
#define PLATFORMERSFML_PLAYER_H

#include "Creature.h"

class Player: public Creature
{
 public:
  //construction
  Player();
  void Setup();

  //methods
  void Move(bool right, bool left);
  void AirWalk();
  void Animate();
  bool DeathAnimate();

  //attributes
  int health;  //how much health the player has left
  bool jumping;  //wheter the player is jumping or not (false when falling)
  float jumpspeed = 50.0f;  //starting jumpspeed, for the first burst of speed
  float fall = 2.0f;  //rate at which the power of the jump decreases
  int airdirection;  //direction the player was moving before they jumped, and are now locked into
  float playerspeed = 10;  //the player's walking speed

  sf::Texture live_texture;
  sf::Texture dead_texture;
  bool dead;  //whether the player is dead or not
  bool deadtex;  //checks to see if the death animation texture is applied
  float count;  //counts to see if the player has finished dying

  int no_flip;  //the rect width for facing right
  int flip;   //the rect width for facing left
  int orient;  //current direction the player is facing

};

#endif // PLATFORMERSFML_PLAYER_H
