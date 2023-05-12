//
// Created by NESco on 26/04/2022.
//

#include "Door.h"

Door::Door()
{
}

void Door::Setup() //sets up the door, making it reappear if gone
{
  Solids::Setup("Data/Images/gate_sheet.png");
  door_rect = sf::IntRect(0, 0,(solid_texture.getSize().x)/3,(solid_texture.getSize().y));
  form.setTextureRect(door_rect);
  alive = true;
}