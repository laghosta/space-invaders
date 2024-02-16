#pragma once
#include "raylib.h"
class Block
{
public:
	Block(Vector2 position);
	~Block();
	void Draw();
	Rectangle GetRect();
private: 
	Vector2 position;
	Vector2 size;
	Color color;
};

