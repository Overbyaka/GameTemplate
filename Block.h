#pragma once
enum class Type { Floor, Danger, Door, Coin};
#define FLOOR_COLOR 11111111
#define DANGER_COLOR 33333333
#define DOOR_COLOR 22222222
#define COIN_COLOR 44444444

class Block
{
	Type type;
	int color;
	int height;
	int width;
	int position_x;
	int position_y;

	public:
		Block();
		Block(Type t, int h, int w, int x, int y);
		int getX();
		int getY();
		int getHeight();
		int getWidth();
		int getColor();
		Type getType();
		void setX(int x);
		void setY(int y);
		void setHeight(int h);
		void setWidth(int w);
		void setColor(int c);
		void setType(Type t);
		//Block operator=(const Block block);
};

