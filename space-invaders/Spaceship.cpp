#include "Spaceship.h"
#include <iostream>
Spaceship::Spaceship() {
	texture = LoadTexture("Graphics/spaceship.png");
	shootSound = LoadSound("Sounds/laser.ogg");
	position.x = (GetScreenWidth() - texture.width)/2;
	position.y = GetScreenHeight() - texture.height -100;
	speed = 7;
	lastShootTime = 0.0;
}

Spaceship::~Spaceship() {
	UnloadTexture(texture);
	UnloadSound(shootSound);
}
void Spaceship::Draw() {
	DrawTextureV(texture, position, WHITE);

}

void Spaceship::MoveLeft() {
	position.x -= speed;
	if (position.x < 0) {
		position.x = 0;
	}
}

void Spaceship::MoveRight() {
	position.x += speed;
	if (position.x > GetScreenWidth() - texture.width) {
		position.x = GetScreenWidth() - texture.width;
	}
}
void Spaceship::Shoot() {
	if (GetTime() - lastShootTime >= 0.35) {
		PlaySound(shootSound);
		bullets.push_back(Bullet({position.x + texture.width/2 - 2, position.y}, -7));
		lastShootTime = GetTime();
	}
}

Rectangle Spaceship::GetRect()
{

	return { position.x, position.y, float(texture.width), float(texture.height) };
}

void Spaceship::Reset()
{
	position.x = (GetScreenWidth() - texture.width) / 2;
	position.y = GetScreenHeight() - texture.height - 100;
	bullets.clear();
}
