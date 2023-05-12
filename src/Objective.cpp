//
// Created by NESco on 22/04/2022.
//

#include "Objective.h"

Objective::Objective()
{
}

void Objective::Setup(bool real)  //sets up the objective, with a different texture depending on if it is the final objective (real) or not
{
  std::string filename = "";
  if (real)
  {
    filename = "Data/Images/friend_sheet.png";
    rectnum = 1;
    creature_rect = sf::IntRect((creature_texture.getSize().x / 9) * rectnum, 0,(creature_texture.getSize().x)/9, (creature_texture.getSize().y));//(creature_texture.getSize().y));
    body.setTextureRect(creature_rect);
    anim = true;
  }
  else
  {
    filename = "Data/Images/friend_splash.png";
  }
  Creature::Setup(filename, 8);

}

void Objective::Animate()  //animates the real one
{
  if (Creature::Animate(0.25))
  {
    if (rectnum == 0)  //the first frame of the spritesheet is an idle pose, so the animation skips it.
    {rectnum = 1;}
    creature_rect = sf::IntRect(
      (creature_texture.getSize().x / 9) * rectnum,
      0,
      (creature_texture.getSize().x / 9),
      (creature_texture.getSize().y));
    body.setTextureRect(creature_rect);
  }
}