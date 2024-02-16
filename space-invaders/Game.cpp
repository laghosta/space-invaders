#include "Game.h"
#include <iostream>
#include "Obstacle.h"

Game::Game() {
	music = LoadMusicStream("Sounds/music.ogg");
	explosionSound = LoadSound("Sounds/explosion.ogg");
	PlayMusicStream(music);
	InitGame();
}
Game::~Game() {
	UnloadMusicStream(music);
	UnloadSound(explosionSound);

}

void Game::Update() {

	if (running) {

		float mysteryShipCurrentTime = GetTime();

		if (mysteryShipCurrentTime - lastTimeMysteryShipSpawned > mysteryShipSpawnInterval) {
			mysteryship.Spawn();
			lastTimeMysteryShipSpawned = mysteryShipCurrentTime;
			mysteryShipSpawnInterval = GetRandomValue(10, 20);
		}


		for (auto& bullet : spaceship.bullets)
		{
			bullet.Update();
		}

		MoveAliens();

		float currentTime = GetTime();

		if (currentTime - lastAlienShootTime >= alienShootingInterval && !aliens.empty()) {
			AlienShoot();
			lastAlienShootTime = currentTime;
		}

		for (auto& alienBullet : alienBullets) {
			alienBullet.Update();
		}
		mysteryship.Update();
		DeleteInactiveBullets();
		CheckCollisions();
	}
	else if(IsKeyPressed(KEY_ENTER)) {
		Reset();
		InitGame();
	}

}

void Game::Draw() {
	for (auto& bullet: spaceship.bullets)
	{
		bullet.Draw();
	}

	for (auto& obstacle : obstacles) {
		obstacle.Draw();
	}

	for (auto& alien: aliens)
	{
		alien.Draw();
	}
	for (auto& alienBullet : alienBullets) {
		alienBullet.Draw();
	}

	spaceship.Draw();
	mysteryship.Draw();

}



void Game::HandleInputs() {
	if (running) {
		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
			spaceship.MoveRight();
		}
		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
			spaceship.MoveLeft();
		}
		if (IsKeyDown(KEY_SPACE) || IsKeyDown(MOUSE_BUTTON_LEFT)) {
			spaceship.Shoot();
		}
	}

}

void Game::DeleteInactiveBullets() {
	for (auto it = spaceship.bullets.begin(); it != spaceship.bullets.end();) {
		if (!it->active) {
			it = spaceship.bullets.erase(it);
		}
		else {
			++it;
		}
	}
	for (auto it = alienBullets.begin(); it != alienBullets.end();) {
		if (!it->active) {
			it = alienBullets.erase(it);
		}
		else {
			++it;
		}
	}
}

std::vector<Obstacle> Game::CreateObstacles() {
	const int obstacleWidth = Obstacle::grid[0].size()*3;
	const int obstaclesGap = (GetScreenWidth() - obstacleWidth * 4) / 5;

	for (int i = 0; i < 4; i++)
	{
		float offsetX = (i + 1) * obstaclesGap + i * obstacleWidth;
		obstacles.push_back(Obstacle({ offsetX, float(GetScreenHeight()- 200) }));
	}

	return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
	std::vector<Alien> aliens;
	for (int row = 0; row < 5; row++)
	{
		for (int col = 0; col < 11; col++)
		{
			int alienType;
			if (row == 0) {
				alienType = 3;
			}
			else if (row == 1 || row == 2) {
				alienType = 2;
			}
			else {
				alienType = 1;
			}

			float x = col * 55 + 75;
			float y = row * 55 + 100;
			aliens.push_back(Alien(alienType, { x,y }));
		}
	}

	return aliens;
}

void Game::MoveAliens() {

	for (auto& alien : aliens)
	{
		if (alien.position.x > GetScreenWidth() - 25 - alien.textures[0].width) {
			aliensDirection = -1;
			MoveDownAliens(5);

		}
		if (alien.position.x < 25) {
			aliensDirection = 1;
			MoveDownAliens(5);
		}
		alien.Update(aliensDirection);

	}	
	
}

void Game::MoveDownAliens(int distance) {
	for (auto& alien : aliens)
	{
		alien.position.y += distance;
	}
}

void Game::AlienShoot()
{
	int randValue = GetRandomValue(0, aliens.size() - 1);
	Alien& alien = aliens[randValue];
	float xPos = alien.position.x + alien.textures[alien.type - 1].width/2;
	float yPos = alien.position.y + alien.textures[alien.type - 1].height;
	alienBullets.push_back(Bullet({ xPos, yPos}, 3));
}

void Game::CheckCollisions() {
	for (auto& bullet: spaceship.bullets){
		auto it = aliens.begin();
		while (it != aliens.end()) {
			if(CheckCollisionRecs(bullet.GetRect(), it->GetRect())){
				PlaySound(explosionSound);
				bullet.active = false;
				if (it->type == 1) {
					score += 100;
				}
				else if (it->type == 2) {
					score += 200;
				}
				else if (it->type == 3) {
					score += 300;
				}
				it = aliens.erase(it);
			}
			else {
				++it;
			}
		}
		
		for (auto& obstacle: obstacles)
		{
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(bullet.GetRect(), it->GetRect())) {
					bullet.active = false;
					it = obstacle.blocks.erase(it);
				}
				else {
					it++;
				}
			}
		}
		if (mysteryship.alive) {
			if (CheckCollisionRecs(bullet.GetRect(), mysteryship.GetRect())) {
				PlaySound(explosionSound);
				bullet.active = false;
				score += 500;
				mysteryship.alive = false;
			}
		}
		

	}
	for (auto& alienBullet : alienBullets)
	{
		for (auto& obstacle : obstacles)
		{
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(alienBullet.GetRect(), it->GetRect())) {
					alienBullet.active = false;
					it = obstacle.blocks.erase(it);
				}
				else {
					++it;
				}
			}

		}

		if (CheckCollisionRecs(alienBullet.GetRect(), spaceship.GetRect())) {
			alienBullet.active = false;
			lifes--;
			if (lifes < 1) {
				GameOver();
			}
			std::cout << lifes << std::endl;
		}
	}

	for ( auto& alien : aliens)
	{

		for (auto& obstacle:obstacles)
		{
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(alien.GetRect(), it->GetRect())) {
					it = obstacle.blocks.erase(it);
				}
				else {
					it++;
				}
			}
		}

		if (CheckCollisionRecs(alien.GetRect(), spaceship.GetRect())) {
			GameOver();
		}
	}
}

void Game::GameOver() {
	running = false;
	std::cout << "Game Over" << std::endl;
}

void Game::Reset() {
	spaceship.Reset();
	aliens.clear();
	alienBullets.clear();
	obstacles.clear();
	
}
void Game::InitGame() {
	obstacles = CreateObstacles();
	aliens = CreateAliens();
	aliensDirection = 1;
	lastAlienShootTime = 0.0;
	lastTimeMysteryShipSpawned = 0.0;
	mysteryShipSpawnInterval = GetRandomValue(10, 20);
	lifes = 3;
	if (score!= NULL && score > highScore) {
		highScore = score;
	}
	score = 0;
	running = true;
}