
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include "Enemy.h"
#include "Icon.h"
#include "Bar.h"
#include "Item.h"
#include "Platform.h"
#include "Door.h"
#include "Player.h"
#include "Spirit.h"
#include "Objective.h"
#include <SFML/Graphics.hpp>

class Game
{
 public:
  //construction
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  //basic
  void update(float dt);
  void render();
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  void mouseClicked(sf::Event event);
  sf::Text textSetup(sf::Text text, sf::String textstring, int textsize, char textcolour);
  //methods
  void damage();
  void pickup(Item item);
  void ready();
  void cameramove(bool respawn);

 private:
  //windows & views
  sf::RenderWindow& window;
  sf::View view1;
  sf::View view2;

  //text
  sf::Font font;
  sf::Text start_text;
  sf::Text coin_text;
  sf::Text win_text;
  sf::Text lose_text;
  sf::Text restart_text;
  sf::Text tutorial_text_1;
  sf::Text tutorial_text_2;
  sf::Text tutorial_text_3;

  //main menu
  sf::Sprite title_sprite;
  sf::Texture title_texture;
  sf::Sprite menu_background;
  sf::Texture menu_background_texture;

  //backgrounds
  sf::Sprite background;
  sf::Texture background_texture;
  sf::Sprite win_background;
  sf::Texture win_background_texture;
  sf::Sprite lose_background;
  sf::Texture lose_background_texture;

  //player
  Player Eb;
  Spirit eb_wave;

  //objectives
  Objective Flo;
  Objective flo_wave_1;
  Objective flo_wave_2;
  Objective flo_wave_3;

  //UI
  Icon hp1; Icon hp2; Icon hp3; Icon hp4; Icon hp5;
  Icon health[5] = {hp1, hp2, hp3, hp4, hp5};
  Icon coin_icon;
  Bar wave_bar;

  //platforms
  Platform pl1; Platform pl2; Platform pl3; Platform pl4; Platform pl5;
  Platform floaty[5] = {pl1, pl2, pl3, pl4, pl5};
  Platform fl1; Platform fl2; Platform fl3; Platform fl4; Platform fl5; Platform fl6; Platform fl7; Platform fl8; Platform fl9; Platform fl10; Platform fl11; Platform fl12; Platform fl13; Platform fl14; Platform fl15;
  Platform floor[15] = {fl1, fl2, fl3, fl4, fl5, fl6, fl7, fl8, fl9, fl10, fl11, fl12, fl13, fl14, fl15};
  int floormax = 15;  //number of floor plates

  //enemies
  Enemy Molly; Enemy Polly; Enemy Lily; Enemy Millie; Enemy Jill;
  Enemy foes[5] = {Molly, Polly, Lily, Millie, Jill};

  //coins
  Item coin_drop1;
  Item coin1; Item coin2; Item coin3; Item coin4; Item coin5; Item coin6; Item coin7; Item coin8; Item coin9; Item coin10;
  Item coins[11] = {coin1, coin2, coin3, coin4, coin5, coin6, coin7, coin8, coin9, coin10, coin_drop1};

  //keys & gates
  Item key1; Item key2; Item key3; Item key4; Item key5;
  Item keys[5] = {key1, key2, key3, key4, key5};
  Door gate1; Door gate2; Door gate3; Door gate4; Door gate5;
  Door gates[5] = {gate1, gate2, gate3, gate4, gate5};

  //game states
  bool in_menu;
  bool in_game;
  bool in_over;
  bool in_win;
  bool in_tutorial;

  int money; //how many coins the player has collected

  //player direction
  bool left;
  bool right;

  int wave_charge; //how much charge the player has- letting the player summon the spirit only when full

  //enemy hit registration
  int enemyhit;
  bool gothit;
  bool inpain;

  //camera & respawn controls
  int offset;   //camera shift
  int backset;  //respawn location
  int rel_cointextpos; //coin text relative position

};

#endif // PLATFORMER_GAME_H
