#pragma once
#define START_SPEED 16
#define MOVE_SPEED 3
class Hero
{
	int height = 40;
	int width = 40;
	int position_x;
	int position_y;
	int speedY = START_SPEED;
	bool up = true;
	unsigned int color = 5555555;

	public:
		Hero();
		Hero(int x, int y);
		int getX();
		int getY();
		void setX(int x);
		void setY(int y);
		int getSpeedY();
		void setSpeedY(int y);
		int getHeight();
		int getWidth();
		unsigned int getColor();
		void addX(int x);
		void changeUp();
		void update(); //update position_y by speedY or in other words: jumping
};

