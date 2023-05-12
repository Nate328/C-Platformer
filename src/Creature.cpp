//
// Created by NESco on 23/03/2022.
//

#include "Creature.h"
#include <iostream>

Creature::Creature()
{
}

void Creature::Setup(std::string filename, int animmax)  //sets up the creature, making it alive, and resetting the texture and animation
{
  if (!creature_texture.loadFromFile(filename))  //loads the laser image into the game
  {
    std::cout << "health texture didn't load \n";  //checks if the image loaded correctly
  }
  body.setTexture(creature_texture);
  alive = true;
  rectnum = 0;
  rectmax = animmax;
}

void Creature::Move(bool right, bool left, float speed)  //moves the creature left and right, triggering the enemy and player's animations
{
  if (right)
  {
    x += speed;
    anim = true;
  }
  else if (left)
  {
    x -= speed;
    anim = true;
  }
  else
  {
    anim = false;
  }
}

int Creature::Grounded(sf::Sprite platform)  //checks to see if the creature is touching the ground
{
  float player_x_min = body.getPosition().x;
  float player_x_max = body.getPosition().x + body.getGlobalBounds().width;
  float player_y_max = body.getPosition().y + body.getGlobalBounds().height;
  float player_f_min = player_y_max - (body.getGlobalBounds().height / 5);   //this makes a hitbox that only covers the player's feet.
  float platform_x_min = platform.getPosition().x;
  float platform_x_max = platform.getPosition().x + platform.getGlobalBounds().width;
  float platform_y_min = platform.getPosition().y;

  if (player_x_min >= platform_x_min && player_x_min <= platform_x_max || player_x_max >= platform_x_min && player_x_max <= platform_x_max) //sees if the player and platform align on the x axis
  {
    if (player_y_max >= platform_y_min && player_f_min <= platform_y_min) // sees if the player's feet are above the platform
    {
      groundlevel = platform_y_min - body.getGlobalBounds().height;  // sets the player's feet to the level of the platform
      ground = true;
      return 0;
    }
  }
}

bool Creature::Collision(sf::Sprite other)  //checks to see if the creature is touching something
{
  float sxmin = body.getPosition().x; // sets out the bounds for the creature's hitbox
  float sxmax = body.getPosition().x + body.getGlobalBounds().width;
  float symin = body.getPosition().y;
  float symax = body.getPosition().y + body.getGlobalBounds().height;
  float oxmin = other.getPosition().x; // sets out bounds for the other thing's hitbox
  float oxmax = other.getPosition().x + other.getGlobalBounds().width;
  float oymin = other.getPosition().y;
  float oymax = other.getPosition().y + other.getGlobalBounds().height;
  if (
    symin >= oymin && symin <= oymax ||
    symax >= oymin && symax <= oymax) // checks if the creature is touching it
  {
    if (
      sxmin >= oxmin && sxmin <= oxmax ||
      sxmax >= oxmin && sxmax <= oxmax) // creature currently doesn't care about the y
    {
      return true;
    }
    else
    {return false;}
  }
  else
  {return false;}
}

bool Creature::Animate(float rate)  //runs the basic steps for the animtions
{
  if (anim)
  {
    rectnum += rate;
    if (rectnum >= rectmax)  //loops the rectnum
    {
      rectnum = 0;
    }
    if (rectnum - int(rectnum) == 0)  //if rectnum is a whole number (including 0), then it moves onto the next frame
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }

}