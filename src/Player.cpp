//
// Created by NESco on 23/03/2022.
//

#include "Player.h"

Player::Player()
{
}

void Player::Setup()  //sets up the player- their textures, their rect, their position and their health
{
  Creature::Setup("Data/Images/player_sheet.png", 8);
  live_texture.loadFromFile("Data/Images/player_sheet.png");  //despite setting it above, the living texture is stored for later, just in case
  dead_texture.loadFromFile("Data/Images/player_death.png");
  rectnum = 1;
  no_flip = (creature_texture.getSize().x)/8 - 15;
  creature_rect = sf::IntRect((creature_texture.getSize().x / 8) * rectnum, 0, no_flip, (creature_texture.getSize().y));
  flip = -((creature_texture.getSize().x)/8) + 30;
  body.setTextureRect(creature_rect);
  anim = true;
  health = 5;
  dead = false;
  deadtex = false;
  x = 100;
  y = 150;
  jumping = false;
}

void Player::Move(bool right, bool left)  //moves the player side to side, as well as letting them jump
{
  if (!ground || jumping)  //if not touching the ground, or trying not to touch the ground:
  {
    y += 15;  //gravity
    if (jumping) // if they are still holding the jump key
    {
      y -= jumpspeed; // reduce the rate at which the player's vertical momentum decreases jumpspeed cannot start higher than the gravity constant, or the player would speed up at first as they jumped.
      jumpspeed -= fall;             // reduce the effect of that decrease
      if (jumpspeed <= 10) // stops holding the jump key having an inverse effect, where you fall faster
      {
        jumping = false;
      }
    }
    AirWalk();
  }
  else
  {
    y = groundlevel;  //keeps the player on the ground
    Creature::Move(right, left, playerspeed);  //walks left and right
  }

}

void Player::AirWalk()  //used for moving in the air, by fixing the player into their current direction
{
  if(airdirection <= -1)
  {
    Creature::Move(true, false, playerspeed);
  }
  else if (airdirection >= 1)
  {
    Creature::Move(false, true, playerspeed);
  }
}

void Player::Animate()  //animates the player character when they walk
{
  if (Creature::Animate(0.25))
  {
    if (rectnum == 0)  //the first sprite is an idle pose, so the animation skips it
    {rectnum = 1;}
    creature_rect = sf::IntRect(
      (creature_texture.getSize().x / 9) * rectnum,
      0,
      orient,  //applies the texture with a width of either flip or noflip, depending on which direction the player is facing
      (creature_texture.getSize().y));
    body.setTextureRect(creature_rect);
  }
}

bool Player::DeathAnimate()  //animates the player's death
{
  if (!deadtex)  //if the dead texture hasn't been applied yet:
  {
    creature_texture = dead_texture;
    rectnum = 0;  //returns to the start of the animation
    deadtex = true;
    rectmax = 10;  //sets a new rectmax, due to the increased number of frames in use.
    count = 0.0f;
    no_flip -= 50;
  }
  Animate();
  count += 0.25;  //counts along with the frames to determine the point of death
  if (count == 10.0f)  //when it reaches this number, the animation should be finished
  {
    return true;
  }
  else
  {
    return false;
  }
}