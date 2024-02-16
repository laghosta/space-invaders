#include "Bullet.h"
#include <iostream>
Bullet::Bullet(Vector2 position, int speed) {
	this->position = position;
	this->speed = speed;
	size = { 4, 10 };
	active = true;
}
Bullet::~Bullet() {

}

void Bullet::Draw() {
	if (active) {
		DrawRectangleV(position, size, WHITE);
	}
}
void Bullet::Update() {
	position.y +=speed;
	if (active) {
		if (position.y < 25 || position.y > GetScreenHeight() - 100) {
			active = false;
		}
	}
	
}
Rectangle Bullet::GetRect() {
	return { position.x, position.y, size.x, size.y };
 }