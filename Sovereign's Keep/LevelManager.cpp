#include "LevelManager.h"

LevelManager::LevelManager()
{
	Wave = 1;
	WaveTimer = MAX_WAVE_TIME;
	SpawnTickRate = 2.0f; //Spawn an enemy every 2 seconds
}

void LevelManager::update(double dt)
{
	if (WaveTimer > 0)
	{
		WaveTimer -= dt;
	}
	else
	{
		GenerateNextWave();
		WaveTimer = MAX_WAVE_TIME;
		Wave++;
	}

	//TODO - Spawn the enemies here based on tick rate
}

void LevelManager::GenerateNextWave()
{
	//TODO - Change the vector of enemies to spawn for the wave.
	//OPTIONAL - You could also adjust the SpawnTickRate for the new wave.
}

void LevelManager::SpawnEnemy()
{
	// Spawns only one enemy randomly picked from the Wave Vector
}

void LevelManager::SpawnEnemyGroup()
{
	// Should select a group of enemies (min 3) from the Wave vector
	// and spawn them together.
}
