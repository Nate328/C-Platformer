
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

sf::Text Game::textSetup(sf::Text text, sf::String textstring, int textsize, char textcolour)  //sets up the text, its size and its colour.
{
  text.setString(textstring);
  text.setCharacterSize(textsize);
  if (textcolour == 'W') //white text
  {text.setFillColor(sf::Color(255,255,255,255));}
  else if (textcolour == 'G') //grey text
  {text.setFillColor(sf::Color(255,255,255,175));}
  else if (textcolour == 'T') //translucent text
  {text.setFillColor(sf::Color(255,255,255,50));}
  return text;
}

bool Game::init() //sets up most of the game
{
  sf::View newview(sf::FloatRect(0.0f, 0.0f,1080.f, 740.f));  //creates the base view
  view1 = newview;  //game view
  view2 = newview;  //menu view
  window.setView(view1);  //sets the view
  in_menu = true;  //sets the game states
  in_game = false;
  in_over = false;
  in_win = false;
  in_tutorial = false;

  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))  //loads the font for all the text
  {
    std::cout << "font did not load \n";
  }

  start_text.setFont(font);  //sets up the beginning prompt in the main menu
  start_text = textSetup(start_text, "press Enter to start!", 75, 'G');
  start_text.setPosition(
    window.getSize().x / 2 - start_text.getGlobalBounds().width / 2,
    window.getSize().y / 1.2 - start_text.getGlobalBounds().width / 2);

  if (!menu_background_texture.loadFromFile("Data/Images/whitewash.png"))  //loads the menu backgroud image into the game
  {
    std::cout << "background texture didn't load \n";  //checks if the image loaded correctly
  }
  menu_background.setTexture(menu_background_texture);
  menu_background.setPosition(0,0);

  if (!title_texture.loadFromFile("Data/Images/title.png")) //loads the title image
  {
    std::cout << "title texture didn't load \n";
  }
  title_sprite.setTexture(title_texture);
  title_sprite.setPosition(window.getSize().x / 2 - title_sprite.getGlobalBounds().width / 2,0);



  if (!background_texture.loadFromFile("Data/Images/background.png"))  //loads the background image into the game
  {
    std::cout << "background texture didn't load \n";  //checks if the image loaded correctly
  }
  background.setTexture(background_texture);

  if (!win_background_texture.loadFromFile("Data/Images/background_win.png"))  //loads the victory screen background into the game
  {
    std::cout << "background texture didn't load \n";  //checks if the image loaded correctly
  }
  win_background.setTexture(win_background_texture);
  win_background.setPosition(-80,-65);

  if (!lose_background_texture.loadFromFile("Data/Images/background_lose.png"))  //loads the failure screen background image into the game
  {
    std::cout << "background texture didn't load \n";  //checks if the image loaded correctly
  }
  lose_background.setTexture(lose_background_texture);
  lose_background.setPosition(-20,-70);

  tutorial_text_1.setFont(font);  //sets up the tutorial text
  tutorial_text_1 = textSetup(tutorial_text_1, "Get to the end, and collect as many coins as you can", 40, 'W');
  tutorial_text_1.setPosition(
    0,
    200);
  tutorial_text_2.setFont(font);
  tutorial_text_2 = textSetup(tutorial_text_2, "Left: A   Right: D  Jump: Space  Summon: Click", 40, 'W');
  tutorial_text_2.setPosition(
    0,
    300);
  tutorial_text_3.setFont(font);
  tutorial_text_3 = textSetup(tutorial_text_3, "Slimes hurt, Keys unlock gates. Good luck!", 40, 'W');
  tutorial_text_3.setPosition(
    0,
    400);


  win_text.setFont(font);  //sets up the big title shown after winning
  win_text = textSetup(win_text, "You Win!", 125, 'W');
  win_text.setPosition(
    window.getSize().x / 2 - win_text.getGlobalBounds().width / 2,
    0);

  lose_text.setFont(font);  //sets up the big title shown after losing
  lose_text = textSetup(lose_text, "You Lose!", 125, 'W');
  lose_text.setPosition(
    window.getSize().x / 2 - lose_text.getGlobalBounds().width / 2,
    0);

  restart_text.setFont(font);  //sets up the beginning prompt in the victory and failure scenes
  restart_text = textSetup(restart_text, "press Enter to start again!", 75, 'G');
  restart_text.setPosition(
    window.getSize().x / 2 - restart_text.getGlobalBounds().width / 2,
    window.getSize().y / 1.2 - restart_text.getGlobalBounds().width / 2);

  return true;
}

void Game::update(float dt)
{
  if (in_game && !Eb.dead)
  {
    /// PLAYER CONTROL///
    Eb.Move(right, left);  //moves the player
    Eb.ground      = false;
    eb_wave.ground = false;
    for (int i = 0; i < floormax; i++)  //checks to see if the player and/or their wave are grounded
    {
      Eb.Grounded(floor[i].form);
      eb_wave.Grounded(floor[i].form);
      Eb.Grounded(floaty[i].form);
      eb_wave.Grounded(floaty[i].form);
    }

    if (Eb.ground)
    {
      Eb.Animate();  //animates the player when walking
    }

    Eb.body.setPosition(Eb.x, Eb.y);  //moves the player
    if (Eb.y >= window.getSize().y)  //respawns the player if they fall off
    {
      damage();
      Eb.y = 200;
      Eb.x = backset;  //teleports them back to the checkpoint
      cameramove(false);  //moves the camera back too
      Eb.body.setPosition(Eb.x, Eb.y);
    }

    /// WAVE CONTROL///
    if (!eb_wave.ground)  //makes the wave fall if it isn't on the ground
    {
      eb_wave.Drop();
      eb_wave.body.setPosition(eb_wave.x, eb_wave.y);
    }
    if (wave_charge < 500)  //increases the charge, if it hasn't reached the max
    {
      wave_charge += 1;
      if (wave_charge % 25 == 0)
      {
        wave_bar.Fill(false); //at intervals, updates the charge bar
      }
    }

    /// CAMERA///
    if (Eb.x >= (window.getSize().x - 500) + offset)  //if the player nears the end of the screen, move it along
    {
      offset += 10;
      cameramove(true);
    }

    /// ITEM MANAGEMENT///
    for (int i = 0; i < 11; i++)  //check each of the coins
    {
      coins[i].Animate();
      if (coins[i].Collision(Eb.body) && coins[i].alive) //if the player touches the coin, pick it up
      {
        pickup(coins[i]);
        coins[i].alive = false;
      }
    }

    for (int i = 0; i < 5; i++)  //checks the keys and gates
    {
      if (
        (keys[i].Collision(Eb.body) || (keys[i].Collision(eb_wave.body))) &&
        keys[i].alive)  //if the player touches a key, make that and its gate disappear
      {
        keys[i].alive  = false;
        gates[i].alive = false;
      }
      if (gates[i].alive)
      {
        if (Eb.Collision(gates[i].form))  //if the gate is alive and the player touches it
        {
          Eb.x -= 15;  //they get pushed back
          Eb.body.setPosition(Eb.x, Eb.y);
        }
      }
    }

    /// OBJECTIVE
    Flo.Animate();  //flo's cloak flows just like the player's
    if (Eb.Collision(Flo.body))  //if the player touches them, the game ends and they win
    {
      in_game = false;
      window.setView(view2);
      in_win = true;
    }
    if (Eb.Collision(flo_wave_1.body) && flo_wave_1.alive)  //for each of flo's waves, set the checkpoint to their location
    {
      backset          = flo_wave_1.body.getPosition().x;
      flo_wave_1.alive = false;   //stops them from being activated more than once
    }
    if (Eb.Collision(flo_wave_2.body) && flo_wave_2.alive)
    {
      backset          = flo_wave_2.body.getPosition().x;
      flo_wave_2.alive = false;
    }
    if (Eb.Collision(flo_wave_3.body) && flo_wave_3.alive)
    {
      backset          = flo_wave_3.body.getPosition().x;
      flo_wave_3.alive = false;
    }

    /// ENEMY CONTROL///
    gothit = false;
    for (int i = 0; i < 5; i++) //checks each enemy
    {
      if (foes[i].alive)
      {
        enemyhit = 0;
        foes[i].Move();
        foes[i].body.setPosition(foes[i].x, foes[i].y);
        enemyhit = foes[i].PlayerCollision(Eb.body);
        if (enemyhit >= 1) //if the player and enemy touch
        {
          if (enemyhit == 2) //if the player didn't land on the enemy's head
          {
            gothit = true;
            if (!inpain)  //if the player has just taken damage:
            {
              damage();
              inpain = true;
            }
          }
          else if (enemyhit == 1)  //if the player landed on the enemy's head
          {
            money += 1;  //get money, and kill it
            coin_text.setString(std::to_string(money));
          }
        }
        if (foes[i].PlayerCollision(eb_wave.body) >= 1)  //if the spirit landed on them:
        {
          foes[i].alive = false;  //kill the enemy
          coins[10].form.setPosition(foes[i].body.getPosition().x, foes[i].body.getPosition().y + 20);  //place a coin where they died
          coins[10].alive = true;
        }
      }
    }
    if (!gothit)  //if the player hasn't touched an enemy for a while, their invincibility disappears
    {
      inpain = false;
    }
  }
    /// OTHER GAME STATES///
  if (in_game && Eb.dead)  //when the player is dead
  {
      if (Eb.DeathAnimate())  //run the death animation, until it's done.
      {
        in_game = false;
        window.setView(view2);  //reset the camera
        in_over = true;  //go to the defeat screen
      }
  }
  if (!in_game)
  {
      window.setView(view2);  //makes sure the normal camera, not the game camera, is used outside of the game
  }
}

void Game::render()
{
  if (in_menu)
  {
    window.draw(menu_background);
    window.draw(title_sprite);
    window.draw(start_text);
  }
  if (in_tutorial)
  {
    window.draw(tutorial_text_1);
    window.draw(tutorial_text_2);
    window.draw(tutorial_text_3);
  }
  if (in_game)
  {
    window.draw(background);
    ///PLAYER///
    window.draw(Eb.body);
    if (eb_wave.alive)
    {window.draw(eb_wave.body);}

    ///OBJECTIVES///
    window.draw(Flo.body);
    window.draw(flo_wave_1.body);
    window.draw(flo_wave_2.body);
    window.draw(flo_wave_3.body);

    ///UI///
    for (int i = 0; i < Eb.health; i++)
    {  window.draw(health[i].picture);}
    window.draw(wave_bar.picture);
    window.draw(coin_text);
    window.draw(coin_icon.picture);

    ///COINS///
    for (int i = 0; i < 11; i++)
    {
    if (coins[i].alive)
    {window.draw(coins[i].form);}
    }

    ///KEYS & GATES///
    for (int i = 0; i < 5; i++)
    {
      if (keys[i].alive)
      {window.draw(keys[i].form);}
      if (gates[i].alive)
      {window.draw(gates[i].form);}
      ///ENEMIES///
      if(foes[i].alive)
      {window.draw(foes[i].body);}
    }

    ///FLOOR & PLATFORMS
    for (int i = 0; i < floormax; i++)
    {window.draw(floor[i].form);}
    for (int i = 0; i < floormax; i++)
    {window.draw(floaty[i].form);}
  }
  if (in_win)
  {
    window.draw(win_background);
    window.draw(win_text);
  }
  if (in_over)
  {
    window.draw(lose_background);
    window.draw(lose_text);
  }
  if (in_win || in_over)
  {
    window.draw(restart_text);
  }
}

void Game::ready()
{
  ///CAMERA RESET///
  sf::View newview(sf::FloatRect(0.0f, 0.0f,1080.f, 740.f));
  view1 = newview;
  view2 = newview;
  window.setView(view1);
  offset = 0;

  ///PLAYER///
  Eb.Setup();
  Eb.body.setPosition(200,300);
  Eb.health = 5;
  left = false;
  right = false;
  gothit = false;
  inpain = false;

  ///WAVE///
  eb_wave.Setup();
  wave_charge = 0;

  backset = 200;  //resets the respawn point

  ///OBJECTIVES///
  Flo.Setup(true);
  Flo.body.setPosition(9500, 432);
  flo_wave_1.Setup(false);
  flo_wave_1.body.setPosition(800, 432);
  flo_wave_2.Setup(false);
  flo_wave_2.body.setPosition(3700, 432);
  flo_wave_3.Setup(false);
  flo_wave_3.body.setPosition(6400,232);

  ///PLATFORMS///
  for (int i = 0; i < 6; i++)
  {
    floor[i].Setup("Data/Images/floor_chunk.png");
    floor[i].form.setPosition((i*300), 600);
  }
  floaty[0].Setup("Data/Images/platform_mid.png");
  floaty[0].form.setPosition(2000, 400);
  for (int i = 6; i < 9; i++)
  {
    floor[i].Setup("Data/Images/floor_chunk.png");
    floor[i].form.setPosition((i*300)+1300, 600);
  }
  floor[9].Setup("Data/Images/floor_chunk.png");
  floor[9].form.setPosition((9*300)+1700, 600);
  floor[10].Setup("Data/Images/floor_chunk.png");
  floor[10].form.setPosition((9*300)+2200, 600);
  for (int i = 1; i < 3; i++)
  {
    floaty[i].Setup("Data/Images/platform_mid.png");
    floaty[i].form.setPosition((i*800)+4700, 400);
  }
  floaty[3].Setup("Data/Images/platform_mid.png");
  floaty[3].form.setPosition(7300, 700);
  floaty[4].Setup("Data/Images/platform_mid.png");
  floaty[4].form.setPosition((4*800)+4700, 450);
  for (int i = 11; i < 15; i++)
  {
    floor[i].Setup("Data/Images/floor_chunk.png");  //8100
    floor[i].form.setPosition((i*300)+5200, 600);
  }


  ///ENEMIES///
  foes[0].Setup(400,520);
  foes[0].body.setPosition(400, 520);
  foes[1].Setup(2400, 320);
  foes[1].body.setPosition(2400, 320);
  foes[2].Setup(5000, 520);
  foes[2].body.setPosition(5000, 520);
  foes[3].Setup(7700, 620);
  foes[3].body.setPosition(7700, 620);
  foes[4].Setup(8680, 520);
  foes[4].body.setPosition(8680, 520);

  ///MONEY///
  for (auto & coin : coins)
  {
    coin.Setup("Data/Images/coin_sheet.png");
  }
  coins[0].form.setPosition(50, 430);
  coins[1].form.setPosition(600, 430);
  coins[2].form.setPosition(2200, 230);
  coins[3].form.setPosition(2700, 480);
  coins[4].form.setPosition(3400, 430);
  coins[5].form.setPosition(4700, 430);
  coins[6].form.setPosition(5700, 230);
  coins[7].form.setPosition(7200, 330);
  coins[8].form.setPosition(8000, 230);
  coins[9].form.setPosition(8150, 230);

  coins[10].alive = false;  //this is the coin that appears when enemies die




  ///KEY & GATE SETUP///
  for (int i = 0; i < 5; i++)
  {
    keys[i].Setup("Data/Images/key_sheet.png");
    gates[i].Setup();
  }
  keys[0].form.setPosition(1500, 350);
  gates[0].form.setPosition(1700, 300);
  keys[1].form.setPosition(2700, 550);
  gates[1].form.setPosition(3100, 250);
  keys[2].form.setPosition(3600, 50);
  keys[3].form.setPosition(6200, 150);
  gates[3].form.setPosition(6000, -100);
  keys[4].form.setPosition(9100, 350);
  gates[2].form.setPosition(9200, 200);  //gate 2 is at the end, even though its key is earlier.
  gates[4].form.setPosition(9300, 200);


  ///UI///
  for (int i = 0; i < 5; i++)
  {
    health[i].Setup("Data/Images/flame.png", (40 * i));
    health[i].picture.setPosition(40 * i,10);
  }
  coin_icon.Setup("Data/Images/coin.png", window.getSize().x - 250);
  coin_icon.picture.setPosition(window.getSize().x - 250, 15);
  coin_text.setFont(font);  //sets up the coin1 counter
  coin_text = textSetup(coin_text, std::to_string(money), 75, 'G');
  coin_text.setPosition(
    (window.getSize().x - 150),0);
  rel_cointextpos= window.getSize().x - 150;
  wave_bar.Setup(300);
  wave_bar.picture.setPosition(300, 0);

  background.setPosition(0, 0);  //resets background position
}

void Game::keyPressed(sf::Event event)
{
  if (in_tutorial || in_win || in_over)  //menu options:
  {
    if (event.key.code == sf::Keyboard::Enter)  //when enter is pressed start the game, but first:
    {
      in_menu = false;
      in_over = false;  //ensure the game states are correctly set
      in_win = false;
      in_tutorial = false;
      money = 0;  //reset the player's money
      coin_text.setString("0");
      ready();  //resets the level
      in_game = true;
    }
  }
  if(in_menu)
  {
    in_menu = false;
    in_tutorial = true;
  }
  if (in_game)
  {
    if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
    {
      left = true;   //moves the player left, and orients the sprite as such
      Eb.orient = Eb.flip;
    }
    if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
    {
      right = true;    //moves the player right, and orients the sprite as such
      Eb.orient = Eb.no_flip;
    }
    if (event.key.code == sf::Keyboard::Space)
    {
      if (Eb.ground)  //if the player jumps off the ground:
      {
        Eb.y -= 50;  //give them an initial boost off the ground
        Eb.jumpspeed = 40;   //sets the initial jump speed
        Eb.fall = 1.5;  //sets the rate of decrease
        Eb.jumping = true;
        if (right)  //fixes the player's direction
        {Eb.airdirection = -1;}
        else if (left)
        {Eb.airdirection = 1;}
        else
        {Eb.airdirection = 0;}
      }
    }
  }
}

void Game::mouseClicked(sf::Event event)
{
  if (in_tutorial || in_win || in_over)   //identical to if the player presses enter
  {
    in_menu = false;
    in_over = false;
    in_win = false;
    in_tutorial = false;
    money = 0;
    coin_text.setString("0");
    ready();
    in_game = true;
  }
  if(in_menu)
  {
    in_menu = false;
    in_tutorial = true;
  }
  if (in_game)
  {
    if (wave_charge == 500)  //if the player has the charge to do so, summon a wave.
    {
      eb_wave.x = sf::Mouse::getPosition(window).x - 50 + offset;  //the summon's head is approximately centered with the cursor
      eb_wave.y = sf::Mouse::getPosition(window).y - 100;
      eb_wave.body.setPosition(eb_wave.x, eb_wave.y);
      eb_wave.alive = true;
      wave_charge = 0;  //reset the charge value
      wave_bar.Fill(true);  //empty the charge bar
    }
  }
}

void Game::keyReleased(sf::Event event)
{
  if (in_game)
  {
    if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
    {
      left = false;  //stops the player going left when they let go
    }
    if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
    {
      right = false;  //stops the player going right when they let go
    }
    if (event.key.code == sf::Keyboard::Space)
    {
      Eb.fall = 4;  //increases the speed at which the player loses height, allowing for variable jump heights
    }
  }
}

void Game::damage()  //reduces the player's health and activates the dead state
{
  Eb.health -= 1;
  health[Eb.health].alive = false;  //updates the UI
  if (Eb.health <= 0)
  {
    Eb.dead = true;
  }
}

void Game::pickup(Item item)  //updates the UI when the player collects a coin
{
  if (item.type == 'c')
  {
    money += 1;
    coin_text.setString(std::to_string(money));
  }
}

void Game::cameramove(bool respawn)  //moves the camera and the UI
{
  if (respawn)  //if the player is merely moving forward, just move the view forward with them
  {view1.move(10.f, 0.f);}
  else  //if the player falls off and needs to be respawned, then adjust the view location and the offset accordingly
  {view1.move(((-offset)+backset)-200, 0.f);
  offset = backset - 200;}
  background.setPosition(offset, 0);  //moves the background
  coin_icon.picture.setPosition(coin_icon.relpos + offset, 15);  //moves all the UI
  coin_text.setPosition( rel_cointextpos+ offset, 0);   //it uses their relative positions, so that they dont all clump together, and stay where they should on the screen.
  wave_bar.picture.setPosition(wave_bar.relpos + offset, 0);
  for (int i = 0; i < 5; i++)
  {
    health[i].picture.setPosition(health[i].relpos + offset, 10);
  }
  window.setView(view1);  //updates the view
}

