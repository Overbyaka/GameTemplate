#include "Level.h"

//constructors
Level::Level()
{

}
Level::Level(int x, int y, Block *m, int n)
{
	startPositionX = x;
	startPositionY = y;
	this->n = n;
	map = new Block[n];
	for (int i = 0; i < n; i++)
	{
		map[i].setX(m[i].getX());
		map[i].setY(m[i].getY());
		map[i].setHeight(m[i].getHeight());
		map[i].setWidth(m[i].getWidth());
		map[i].setColor(m[i].getColor());
		map[i].setType(m[i].getType());
	}
	//map = m;
}
Level::~Level()
{
	delete[] map;
}

//getters, setters
int Level::getStartX()
{
	return startPositionX;
}
int Level::getStartY()
{
	return startPositionY;
}
int Level::getLength()
{
	return n;
}
Block Level::getBlock(int i)
{
	return map[i];
}
//methods
Level& Level::operator=(const Level& level)
{

	startPositionX = level.startPositionX;
	startPositionY = level.startPositionY;
	n = level.n;
	map = new Block[n];
	for (int i = 0; i < n; i++)
	{
		map[i].setX(level.map[i].getX());
		map[i].setY(level.map[i].getY());
		map[i].setHeight(level.map[i].getHeight());
		map[i].setWidth(level.map[i].getWidth());
		map[i].setColor(level.map[i].getColor());
		map[i].setType(level.map[i].getType());
	}

	return *this;
}
