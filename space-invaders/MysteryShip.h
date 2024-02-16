#pragma once
#include <raylib.h>
class MysteryShip
{
public:
	MysteryShip();
	~MysteryShip();
	bool alive;
	void Draw();
	void Update();
	void Spawn();
	Rectangle GetRect();

private:
	Texture2D texture;
	Vector2 position;
	int speed;
};

