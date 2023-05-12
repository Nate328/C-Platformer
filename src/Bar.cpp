//
// Created by NESco on 27/04/2022.
//

#include "Bar.h"

Bar::Bar()
{
}

void Bar::Setup(int pos)  //sets up the sprite and its relative position
{
  Icon::Setup("Data/Images/wave_bar.png", pos);
  bar_rect = sf::IntRect(0, (icon_texture.getSize().x / 14) * rectnum,(icon_texture.getSize().x), (icon_texture.getSize().y)/20);
  picture.setTextureRect(bar_rect);
}

void Bar::Fill(bool empty)  //animates the abr, filling it up as charge accumulates
{
  if (empty) //resets it and starts refilling
  {
    rectnum = -1;
  }
  if (rectnum <= 19)  //stops it trying to go over the limit
  {
    rectnum += 1;

    bar_rect = sf::IntRect(  //applies the next sprite down on the sheet
    0,
    (icon_texture.getSize().x / 14) * rectnum,
    (icon_texture.getSize().x),
    (icon_texture.getSize().y) / 20);
    picture.setTextureRect(bar_rect);
  }
}