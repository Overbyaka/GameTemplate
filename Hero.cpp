#include "Hero.h"
//constructors
Hero::Hero()
{
	position_x = 0;
	position_y = 0;
}
Hero::Hero(int x, int y)
{
	position_x = x;
	position_y = y;
}

//getters, setters
int Hero::getX()	
{
	return position_x;
}
int Hero::getY()
{
	return position_y;
}
void Hero::setX(int x)
{
	position_x = x;
	return;
}
void Hero::setY(int y)
{
	position_y = y;
	return;
}
int Hero::getSpeedY()
{
	return speedY;
}
void Hero::setSpeedY(int y)
{
	speedY = y;
	return;
}
int Hero::getHeight()
{
	return height;
}
int Hero::getWidth()
{
	return width;
}
unsigned int Hero::getColor()
{
	return color;
}

//methods

void Hero::addX(int x)
{
	position_x += x;
	return;
}
void Hero::changeUp()
{
	up = !up;
	return;
}
void Hero::update()
{
	position_y -= speedY;
	if (up)
		speedY -= 1;
	else
		speedY += 1;
	/*if (speedY == START_SPEED && up)
		this->changeUp();*/

}
