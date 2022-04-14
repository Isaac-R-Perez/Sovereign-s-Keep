#pragma once
#include <vector>
#include "Game.h"
#include "Enemy.h"

const float MAX_WAVE_TIME = 60.0f;

class LevelManager
{
private:
	int Wave; //The current wave the level is on.
	float WaveTimer; //How long the current wave lasts
	float SpawnTickRate; //What interval to spawn enemies in the current wave.

	//TODO - Have a vector filled with enemies to spawn for the current wave.

public:
	LevelManager();
	void update(double dt);
	void GenerateNextWave();

	void SpawnEnemy();
	void SpawnEnemyGroup();
};