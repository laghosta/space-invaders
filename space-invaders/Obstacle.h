#pragma once
#include <raylib.h>
#include <vector>
#include "Block.h"
class Obstacle
{
public:
	Obstacle(Vector2 position);
	void Draw();
	std::vector<Block> blocks;
	static std::vector<std::vector<int>> grid;
	Vector2 position;
private:
};
	
