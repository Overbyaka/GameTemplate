#pragma once
#include "Block.h"
class Level
{
	int startPositionX;
	int startPositionY;
	Block* map;
	int n;
	public:
		Level();
		Level(int x, int y, Block *m, int n);
		~Level();
		int getStartX();
		int getStartY();
		int getLength();
		Block getBlock(int i);
		Level& operator=(const Level& level);
		void deleteCoinByCoords(int x, int y);
		void restartCoin();
};

