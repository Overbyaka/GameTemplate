#include "Block.h"

//constructors
Block::Block()
{

}
Block::Block(Type t, int h, int w, int x, int y)
{
	type = t;
	height = h;
	width = w;
	position_x = x;
	position_y = y;
	switch (type)
	{
		case Type::Floor:
			color = FLOOR_COLOR;
			break;
		case Type::Danger:
			color = DANGER_COLOR;
			break;
		case Type::Door:
			color = DOOR_COLOR;
			break;
	}
}

//getters, setters
int Block::getX()
{
	return position_x;
}
int Block::getY()
{
	return position_y;
}
int Block::getHeight()
{
	return height;
}
int Block::getWidth()
{
	return width;
}
int Block::getColor()
{
	return color;
}
Type Block::getType()
{
	return type;
}

void Block::setX(int x)
{
	position_x = x;
	return;
}
void Block::setY(int y)
{
	position_y = y;
	return;
}
void Block::setHeight(int h)
{
	height = h;
	return;
}
void Block::setWidth(int w)
{
	width = w;
	return;
}
void Block::setColor(int c)
{
	color = c;
	return;
}
void Block::setType(Type t)
{
	type = t;
	return;
}
//Block& Block::operator=(const Block block)
//{
//
//		type = block.type;
//		color = block.color;
//		height = block.height;
//		width = block.width;
//		position_x = block.position_x;
//		position_y = block.position_y;
//
//
//	return *this;
//}

