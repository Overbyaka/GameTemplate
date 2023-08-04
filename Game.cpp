#include "Engine.h"
#include "Hero.h"
#include "Level.h"
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include "Number.h"


//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

//SCREEN_WIDTH 1024
//SCREEN_HEIGHT 768

Hero hero;
double currentTime;
Block *blocks1;
Block* blocks2;
int n1;
int n2;
Level* level;
int m = 2;
int score;
Number number;
int tempLevel;

// initialize game data in this function
void initialize()
{
    currentTime = clock();
    n1 = 17;
    blocks1 = new Block[n1]{
        Block(Type::Floor, 20, 1024, 0, 0),
        Block(Type::Floor, 768, 20, 0, 0),
        Block(Type::Floor, 768, 20, 1004, 0),
        Block(Type::Floor, 20, 1024, 0, 748),
        Block(Type::Floor, 2*number.getSize()*(1 + number.getM()), 2*number.getSize()*(number.getN()), SCREEN_WIDTH- 2 * number.getSize() * (number.getN()), 0),
        Block(Type::Danger, 10,30, 500, 748),
        Block(Type::Floor, 20, 900, 0, 600),
        Block(Type::Danger, 10,200, 500, 600),
        Block(Type::Floor, 20, 800, 20, 200),
        Block(Type::Floor, 20, 100, 0, 450),
        Block(Type::Floor, 20, 150, 350, 400),
        Block(Type::Floor, 20, 150, 700, 350),
        Block(Type::Door, 60, 20, 100, 30),
        Block(Type::Coin, 40, 40, 800, 50),
        Block(Type::Floor, 40, 40, 980, 720),
        Block(Type::Floor, 60, 40, 120, 550),
        Block(Type::Floor, 20, 110, 900, 300)
    };
    n2 = 6;
    blocks2 = new Block[n2]{
        Block(Type::Floor, 20, 1024, 0, 0),
        Block(Type::Floor, 768, 20, 0, 0),
        Block(Type::Floor, 768, 20, 1004, 0),
        Block(Type::Floor, 20, 1024, 0, 748),
        Block(Type::Floor, 2 * number.getSize() * (1 + number.getM()), 2 * number.getSize() * (number.getN()), SCREEN_WIDTH - 2 * number.getSize() * (number.getN()), 0),
        Block(Type::Door, 60, 20, 950, 650),
    };
    level = new Level[m]{
        Level(30, 718, blocks1, n1),
        Level(30, 30, blocks2, n2)
    };
    score = 0;
    tempLevel = 0;
    hero.setX(level[tempLevel].getStartX());
    hero.setY(level[tempLevel].getStartY());
    hero.setSpeedY(START_SPEED);
}

void loadLevel()
{
    currentTime = clock();
    hero = Hero(30, 718);
    tempLevel++;
    if (tempLevel == m)
    {
        tempLevel = 0;
        for (int k = 0; k < m; k++)
        {
            level[k].restartCoin();
        }

    }
    hero.setX(level[tempLevel].getStartX());
    hero.setY(level[tempLevel].getStartY());
    hero.setSpeedY(START_SPEED);
    score += 5;
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
  if (is_key_pressed(VK_ESCAPE))
    schedule_quit_game();
  //press left
  if (is_key_pressed(VK_LEFT) && hero.getX() != 0)
  {
      bool checkIsLeft = true;
      int i = 0, j = 0;
      for (i = 0; i < hero.getHeight() && checkIsLeft; i++)
          checkIsLeft = (buffer[hero.getY() + i][hero.getX() - 1] == 0);
      if (checkIsLeft)
      {
          i--;
          for (j = MOVE_SPEED; j > 0; j--)
          {
              if (buffer[hero.getY() + i][hero.getX() - j] == 0)
                  break;
          }
          hero.addX(-j);
      }
      else
      {
          for (int i = 0; i < hero.getHeight(); i++)
          {
              if (buffer[i + hero.getY()][hero.getX() - 1] == DOOR_COLOR)
              {
                  loadLevel();
              }
              else if (buffer[i + hero.getY()][hero.getX() - 1] == COIN_COLOR)
              {
                  score++;
                  level[tempLevel].deleteCoinByCoords(i + hero.getY(), hero.getX() - 1);
              }
          }
      }
  
  }
  //press right
  if (is_key_pressed(VK_RIGHT) && hero.getX()!=(SCREEN_WIDTH-hero.getWidth()))
  {
      bool checkIsRight = true;
      int i = 0, j = 0;
      for (i = 0; i < hero.getHeight() && checkIsRight; i++)
          checkIsRight = (buffer[hero.getY() + i][hero.getX() + hero.getWidth()] == 0);
      if (checkIsRight)
      {
          i--;
          for (j = MOVE_SPEED; j > 0; j--)
          {
              if (buffer[hero.getY() + i][hero.getX() + hero.getWidth() + j-1] == 0)
                  break;
          }
          hero.addX(j);
      }
      else
      {
          for (int i = 0; i < hero.getHeight(); i++)
          {
              if (buffer[i + hero.getY()][hero.getX() + hero.getWidth() + 1] == DOOR_COLOR)
              {
                  loadLevel();
                  break;
              }
              else if (buffer[i + hero.getY()][hero.getX() + hero.getWidth() + 1] == COIN_COLOR)
              {
                  score++;
                  level[tempLevel].deleteCoinByCoords(hero.getX() + hero.getWidth() + 1, i + hero.getY());
                  break;
              }
          }
      }
  }

  //frames
  //auto jumps and check death
  if (clock() - currentTime >= 30)
  {
      currentTime = clock();
      bool checkIsFloor = false;
      bool checkIsRoof = false;
      int i = 0, j = 0;
      
      //check overflow array
      if (hero.getY() + hero.getHeight() - hero.getSpeedY() > SCREEN_HEIGHT)
          checkIsFloor = true;
      if (hero.getY() - hero.getSpeedY() < 0)
          checkIsRoof = true;

      //check floor
      for (i = 0; i < hero.getWidth() && !checkIsFloor; i++)
      {
          checkIsFloor = (buffer[hero.getY() + hero.getHeight() - hero.getSpeedY()][i + hero.getX()] != 0 && buffer[hero.getY() + hero.getHeight() - hero.getSpeedY()][i + hero.getX()] != hero.getColor());
      }
      if (checkIsFloor)
      {
          for (j = hero.getSpeedY(); j < 0; j++)
          {
              if (hero.getY() + hero.getHeight() - hero.getSpeedY() > SCREEN_HEIGHT)
              {
                  j = 0;
                  break;
              }
              if (buffer[hero.getY() + hero.getHeight() - j][i + hero.getX()] == 0)
                  break;
          }
          if (j == 0)
          {
              for (int i = 0; i < hero.getWidth(); i++)
              {
                  if (buffer[hero.getY() + hero.getHeight() + 1][i + hero.getX()] == DANGER_COLOR)
                      initialize();
              }
              hero.setSpeedY(START_SPEED);
          }
          else
              hero.setSpeedY(j);
      }

      //check roof
      for (i = 0; i < hero.getWidth() && !checkIsRoof; i++)
      {
          checkIsRoof = (buffer[hero.getY() - hero.getSpeedY()][i + hero.getX()] != 0 && buffer[hero.getY() - hero.getSpeedY()][i + hero.getX()] != hero.getColor());
      }
      if (checkIsRoof)
      {
          for (j = hero.getSpeedY(); j < 0; j++)
          {
              if (hero.getY()  - hero.getSpeedY() > SCREEN_HEIGHT)
              {
                  j = 0;
                  break;
              }
              if (buffer[hero.getY() - j][i + hero.getX()] == 0)
                  break;
          }
          if (j == 0)
          {
              for (int i = 0; i < hero.getWidth(); i++)
              {
                  if (buffer[hero.getY() - 1][i + hero.getX()] == DOOR_COLOR)
                  {
                      loadLevel();
                  }
                  else if (buffer[hero.getY() - 1][i + hero.getX()] == COIN_COLOR)
                  {
                      score++;
                      level[tempLevel].deleteCoinByCoords(i + hero.getX(), hero.getY() - 1);
                  }
              }
              hero.setSpeedY(-1);
          }
          else
              hero.setSpeedY(-j);
      }

      hero.update();
  }
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
  // clear backbuffer
  memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

 
      //draw Level
      for (int k = 0; k < level[tempLevel].getLength(); k++)
      {
          for (int i = 0; i < level[tempLevel].getBlock(k).getHeight(); i++)
          {
              for (int j = 0; j < level[tempLevel].getBlock(k).getWidth(); j++)
              {
                  buffer[i + level[tempLevel].getBlock(k).getY()][j + level[tempLevel].getBlock(k).getX()] = level[tempLevel].getBlock(k).getColor();
              }
          }
      }
      //draw Hero
      for (int i = 0; i < hero.getHeight(); i++)
      {
          for (int j = 0; j < hero.getWidth(); j++)
          {
              buffer[i + hero.getY()][j + hero.getX()] = hero.getColor();
          }
      }

      //draw score
      int tempX = number.getSize();
      int tempY = number.getSize();
      if (score == 0)
      {
          number.setZero();
          for (int i = number.getM() - 1; i >= 0; i--)
          {
              for (int j = 0; j < number.getN(); j++)
              {
                  if (number.getMap(j, i) == 1)
                  {
                      for (int k = 0; k < number.getSize(); k++)
                      {
                          for (int l = 0; l < number.getSize(); l++)
                          {
                              buffer[tempY + k][SCREEN_WIDTH - (tempX + l)] = hero.getColor();
                          }
                      }
                  }
                  tempY += number.getSize();
              }
              tempY = number.getSize();
              tempX += number.getSize();
          }

      }
      else
      {
          for (int q = score; q > 0; q = q / 10)
          {
              switch (q % 10)
              {
              case 0:
                  number.setZero();
                  break;
              case 1:
                  number.setOne();
                  break;
              case 2:
                  number.setTwo();
                  break;
              case 3:
                  number.setThree();
                  break;
              case 4:
                  number.setFour();
                  break;
              case 5:
                  number.setFive();
                  break;
              case 6:
                  number.setSix();
                  break;
              case 7:
                  number.setSeven();
                  break;
              case 8:
                  number.setEight();
                  break;
              case 9:
                  number.setNine();
                  break;
              }

              for (int i = number.getM() - 1; i >= 0; i--)
              {
                  for (int j = 0; j < number.getN(); j++)
                  {
                      if (number.getMap(j, i) == 1)
                      {
                          for (int k = 0; k < number.getSize(); k++)
                          {
                              for (int l = 0; l < number.getSize(); l++)
                              {
                                  buffer[tempY + k][SCREEN_WIDTH - (tempX + l)] = hero.getColor();
                              }
                          }
                      }
                      tempY += number.getSize();
                  }
                  tempY = number.getSize();
                  tempX += number.getSize();
              }
              tempX += number.getSize();
              number.setNull();
          }
      }
}

// free game data in this function
void finalize()
{
    delete []blocks1;
    delete []blocks2;
    delete []level;
}

