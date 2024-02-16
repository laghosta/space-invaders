#include "MysteryShip.h"

MysteryShip::MysteryShip() {
	
	texture = LoadTexture("Graphics/mystery.png");
	alive = false;
	speed = 5;

}
MysteryShip::~MysteryShip() {
	UnloadTexture(texture);
}
void MysteryShip::Draw() {
	if (alive) {
		DrawTextureV(texture, position, WHITE);
	}
}
void MysteryShip::Update() {
	if (alive) {
		position.x += speed;
		if (position.x > GetScreenWidth() - texture.width - 25 || position.x < 25) {
			alive = false;
		}
	}
}
void MysteryShip::Spawn() {
	position.y = 90;

	int side = GetRandomValue(0, 1);

	if (side == 0) {
		position.x = 25;
		speed = 3;
	}
	else if(side == 1){
		position.x = GetScreenWidth() - texture.width  - 25;
		speed = -3;
	}
	alive = true;
}

Rectangle MysteryShip::GetRect()
{
	if (alive) {
		return { position.x, position.y, float(texture.width), float(texture.height)};
	}
}



