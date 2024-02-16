#pragma once
#include <raylib.h>
#include <vector>
#include "Bullet.h"
class Spaceship
{
public:
	Spaceship();
	~Spaceship();
	std::vector<Bullet> bullets;
	float lastShootTime;
	
	void Draw();
	void MoveLeft();
	void MoveRight();
	void Shoot();

	void Reset();

	Rectangle GetRect();

private:
	Texture2D texture;
	Vector2 position;
	int speed;
	Sound shootSound;
};