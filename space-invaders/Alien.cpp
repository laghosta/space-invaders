#include "Alien.h"


Texture2D Alien::textures[3];

Alien::Alien(int type, Vector2 position) {

	this->type = type;
	this->position = position;

	if (textures[type - 1].id == 0) {

		switch (type) {
		case 1:
			textures[0] = LoadTexture("Graphics/alien_1.png");
			break;
		case 2:
			textures[1] = LoadTexture("Graphics/alien_2.png");
			break;
		case 3:
			textures[2] = LoadTexture("Graphics/alien_3.png");
			break;
		default:
			textures[0] = LoadTexture("Graphics/alien_1.png");
			break;
		}
	}

}


void Alien::Draw() {
	DrawTextureV(textures[type-1], position, WHITE);
}

Rectangle Alien::GetRect()
{
	return { position.x, position.y, float(textures[type-1].width), float(textures[type-1].height) };
}

void Alien::Update(int direction) {
	position.x += direction;
}

int Alien::GetType() {
	return type;
}