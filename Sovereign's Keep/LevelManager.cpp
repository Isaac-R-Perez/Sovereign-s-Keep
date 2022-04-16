#include "LevelManager.h"

LevelManager::LevelManager(Game* g) : game(g)
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

void LevelManager::SpawnSlime_1(float x, float y)
{
	glm::mat4 move = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
	Renderable* enemy = new Enemy(game, 3, static_cast<int>(SPRITE_SHEETS::slime), EnemyType::slime);
	dynamic_cast<Enemy*>(enemy)->setBaseHealth(100.0f);
	dynamic_cast<Enemy*>(enemy)->setBaseMaxHealth(100.0f);
	dynamic_cast<Enemy*>(enemy)->setBaseAttack(20.0f);
	dynamic_cast<Enemy*>(enemy)->setBaseDefense(5.0f);
	dynamic_cast<Enemy*>(enemy)->setBaseMoveSpeed(0.3f);
	dynamic_cast<Enemy*>(enemy)->updatePosition(move);
	game->renderableToPendingAdd(enemy);
}
