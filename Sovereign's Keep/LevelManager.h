#pragma once

#include "Enemy.h"
#include "Game.h"

const float MAX_WAVE_TIME = 60.0f;

class Enemy;
class Game;

class LevelManager
{
private:
	int Wave; //The current wave the level is on.
	float WaveTimer; //How long the current wave lasts
	float SpawnTickRate; //What interval to spawn enemies in the current wave.
	Game* game;
public:
	LevelManager(Game* g);
	void update(double dt);
	void GenerateNextWave();

	void SpawnEnemy();
	void SpawnEnemyGroup();

	//Enemies
	void SpawnSlime_1(float x, float y);
};