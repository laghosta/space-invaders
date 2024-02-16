#include <raylib.h>
#include "Game.h"
#include "Bullet.h"
#include <iostream>
#include "string"
using namespace std;


int main() {

	Color gray = { 29,29,27,255 };
	Color yellow = { 243, 216, 63, 255 };
	const int offset = 50;
	const int windowWidth = 750;
	const int windowHeight = 700;


	InitWindow(windowWidth + offset, windowHeight + 2*offset, "C++ Space Invaders");
	SetTargetFPS(60);
	InitAudioDevice();

	Texture2D spaceshipTexture = LoadTexture("Graphics/spaceship.png");


	Font font = LoadFontEx("Font/monogram.ttf", 64, 0,0);

	Game game;


	while (WindowShouldClose() == false) {
		UpdateMusicStream(game.music);

		game.Update();

		game.HandleInputs();
		
		BeginDrawing();
		ClearBackground(gray);
		
		DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
		DrawLineEx({ 25, 730 }, { 775, 730 }, 3, yellow);
		if (!game.running) {
			DrawTextEx(font, "GAME OVER", { 570,740 }, 34, 2, yellow);
		}
		else {
			DrawTextEx(font, "LEVEL 01", { 570,740 }, 34, 2, yellow);
		}
		
		for (int i = 0; i < game.lifes; i++)
		{
			DrawTextureV(spaceshipTexture, {float(i*55+35), 740}, WHITE);
		}
		DrawTextEx(font, "SCORE", { 50, 15 }, 34, 2, yellow);
		DrawTextEx(font, std::to_string(game.score).c_str(), { 50, 40 }, 34, 2, yellow);

		DrawTextEx(font, "HIGH SCORE", { 575, 15 }, 34, 2, yellow);
		DrawTextEx(font, std::to_string(game.highScore).c_str(), { 575, 40 }, 34, 2, yellow);

		game.Draw();

		EndDrawing();
	}
	CloseWindow();
	CloseAudioDevice();

	return 0;
}