#pragma once
#include <raylib.h>
class Bullet
{
public:
	Bullet(Vector2 position, int speed );
	~Bullet();
	bool active;
	void Update();
	void Draw();
	Rectangle GetRect();

private:
	Vector2 position;
	Vector2 size;
	int speed;

};

