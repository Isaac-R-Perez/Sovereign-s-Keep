#pragma once
#include "Character.h"
/*
* Child of the Character class.
* This class is for all enemy types that the
* game will have.
*/
enum class EnemyType {
	slime,
};

const float ENEMY_WALKING_BASE_TIME = 0.1f;

const float SLIME_WIDTH = 0.04f;
const float SLIME_HEIGHT = 0.04f;

class Enemy: public Character
{
private:
	int soulDrop = 1; //The amount of souls the enemy will drop

	//determines how the enemy acts and renders
	EnemyType type;

	//if false facing right, if true facing left
	bool facingRight;
	bool facingLeft;

	//determines how fast the running animation plays
	float animationTimer;
	int current_frame;


	/*
		KNOCKBACK is possible, just need a buff for it, as well as a direction of the knockback
	*/

	glm::vec3 knockbackDirection;


public:


	Enemy(Game* g, int rOrder, int defaultSpriteSheet, EnemyType Type);


	void render();
	void update(double dt);


	void setSoulDrop(int amt);
	int getSoulDrop();


	//all buffs are searched and all stats are calculated for this frame
	void applySpellBuffs();

	void setKnockbackDirection(glm::vec3 dir) { knockbackDirection = dir; }

	
};

