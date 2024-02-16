#pragma once
#include <raylib.h>
class Alien
{
public:
	Alien(int type, Vector2 position);
	static Texture2D textures[3];
	int type;
	Vector2 position;
	int GetType();
	void Draw();
	Rectangle GetRect();
	void Update(int direction);

private:

};

