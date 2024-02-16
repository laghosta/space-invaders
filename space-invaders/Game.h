#pragma once
#include "Spaceship.h"
#include "Obstacle.h"
#include "Alien.h"
#include "MysteryShip.h"
#include <iostream>
#include <vector>

class Game
{
public:
	Game();
	~Game();
	bool running;
	int lifes;
	int score;
	int highScore;
	void Draw();
	void Update();
	void HandleInputs();
	Music music;

private: 
	Spaceship spaceship;
	MysteryShip mysteryship;
	std::vector<Obstacle> obstacles;
	std::vector<Alien> aliens;
	std::vector<Bullet> alienBullets;
	int aliensDirection;

	constexpr static float alienShootingInterval = 0.5;
	float lastAlienShootTime;

	int mysteryShipSpawnInterval;
	float lastTimeMysteryShipSpawned; 

	Sound explosionSound;

	std::vector<Obstacle> CreateObstacles();
	std::vector<Alien> CreateAliens();
	void MoveAliens();
	void MoveDownAliens(int distance);
	void AlienShoot();
	void DeleteInactiveBullets();
	void CheckCollisions();

	void InitGame();
	void Reset();
	void GameOver();
};

