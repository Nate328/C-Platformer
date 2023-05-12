//
// Created by NESco on 23/03/2022.
//

#include "Enemy.h"

Enemy::Enemy()
{
}

void Enemy::Setup(int X, int Y)  //sets up the enemy, including the left and right bounds of their patrol
{
  Creature::Setup("Data/Images/enemy_sheet.png", 13);
  left = true;
  right = false;
  x = X;
  y = Y;
  rightbound = X + 10;
  leftbound = X - 140;
  creature_rect = sf::IntRect((creature_texture.getSize().y / 14) * rectnum, 0,(creature_texture.getSize().x),(creature_texture.getSize().y/14));
  body.setTextureRect(creature_rect);
}

void Enemy::Move() //moves the enemy left or right
{
  Creature::Move(right, left, enemyspeed);
  if (x >= rightbound)  //when they reach one of their bounds,they head the other way
  {
    left = true;
    right = false;
  }
  else if (x <= leftbound)
  {
    left = false;
    right = true;
  }
  Animate(); //animates the enemy when they move
}

int Enemy::PlayerCollision(sf::Sprite player)  //checks to see if the enemy is touching a player or a spirit
{
  if(Creature::Collision(player))
  {
    float oymax = player.getPosition().y + player.getGlobalBounds().height;
    float pymin = body.getPosition().y;
    float pymid = body.getPosition().y + (body.getGlobalBounds().height / 2); //extra hitbox for the top of the enemy, so it can tell when the player jumps on it
    if (oymax >= pymin && oymax <= pymid)
    {
      alive = false;
      return 1;  //1 means the player killed it
    }
    else
    {
      return 2;  //2 means it hurt the player
    }
  }
  else
  {return 0;}  //0 means they didn't touch
}

void Enemy::Animate()  //animates the enemy
{
  if (Creature::Animate(0.25))
  {
    if (rectnum == 0)
    {rectnum = 1;}
    creature_rect = sf::IntRect(
      (creature_texture.getSize().x / 14) * rectnum,
      0,
      (creature_texture.getSize().x / 14),
      (creature_texture.getSize().y));
    body.setTextureRect(creature_rect);
  }
}
