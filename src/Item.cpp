//
// Created by NESco on 23/03/2022.
//

#include "Item.h"
#include <iostream>

Item::Item()
{
}

void Item::Setup(std::string filename)  //sets up the item, with different sprites and rects depending on if it is a key or a coin
{
  Solids::Setup(filename);
  if (filename == "Data/Images/coin_sheet.png")
  {
    type = 'c';
    rectmax = 15;
    rectpos = 0;
    item_rect = sf::IntRect(0, (solid_texture.getSize().y / 15) * rectpos,(solid_texture.getSize().x),(solid_texture.getSize().y/15));
    form.setTextureRect(item_rect);
    goingup = false;
  }
  if (filename == "Data/Images/key_sheet.png")
  {
    type = 'k';
    rectmax = 4;
    rectpos = 3;
    item_rect = sf::IntRect(0, (solid_texture.getSize().y / 4) * rectpos,(solid_texture.getSize().x),(solid_texture.getSize().y/4));
    form.setTextureRect(item_rect);
    goingup = false;
  }

  alive = true;

}

bool Item::Collision(sf::Sprite other)  //checks to see if the player is touching the item
{
  float oxmin = other.getPosition().x; // sets out the bounds for the player's hitbox
  float oxmax = other.getPosition().x + other.getGlobalBounds().width;
  float oymin = other.getPosition().y;
  float oymax = other.getPosition().y + other.getGlobalBounds().height;
  float pxmin = form.getPosition().x; // sets out bounds for the item's hitbox
  float pxmax = form.getPosition().x + form.getGlobalBounds().width;
  float pymin = form.getPosition().y;
  float pymax = form.getPosition().y + form.getGlobalBounds().height;
  if (
    oymin >= pymin && oymin <= pymax ||
    oymax >= pymin && oymax <= pymax) // checks if the player is touching it
  {
    if (
      oxmin >= pxmin && oxmin <= pxmax ||
      oxmax >= pxmin && oxmax <= pxmax) // player currently doesn't care about the y
    {
      return true;
    }
    else
    {return false;}
  }
  else
  {return false;}
}

void Item::Animate()  //animates the coin, going up and down the spritesheet
{
  if (!goingup)  //goes down until it reaches the bottom of the sheet...
  {
    rectpos += 0.25;  //adds small increments, so it doesn't change frames too fast
    if (rectpos >= rectmax)
    {
      rectpos = rectmax - 1;
      goingup = true;
    }
  }
  if (goingup)  //...at which point it begins to go back up it, looping like this until collected
  {
    rectpos -= 0.25;
    if (rectpos <= 0)
    {
      rectpos = 0;
      goingup = false;
    }
  }
    if (rectpos - int(rectpos) == 0) //every four runs:
    {
      item_rect = sf::IntRect(  //apply the new rect and use the right sprite off the sheet
        0,
        (solid_texture.getSize().y / 15) * rectpos,
        (solid_texture.getSize().x),
        (solid_texture.getSize().y / 15));
      form.setTextureRect(item_rect);
    }
  //}
}
