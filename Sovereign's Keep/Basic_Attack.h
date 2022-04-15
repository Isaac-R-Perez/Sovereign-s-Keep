#pragma once
#include "Renderable.h"
#include "Player.h"
#include "Enemy.h"
/*
	This class will handle all logic related to the player's basic attack, including bullet spawnpoints and modifiers
*/

const float BULLET_WIDTH = 0.025f;
const float BULLET_HEIGHT = 0.02f;

const float BULLET_BASE_SPEED = 0.75f;
const float BASE_DAMAGE = 20.0f;

const float BULLET_LIFETIME = 1.75f;

class Basic_Attack : public Renderable {

public:

	Basic_Attack(Game* g, int rOrder, int defaultSpriteSheet, float ang);
	Basic_Attack(Game* g, int rOrder, int defaultSpriteSheet, float ang, float speedModifier);

	void render();
	void update(double dt);


private:

	//holds the angle that the basic attack flys, in RADIANS
	float angle;

	float damage;

	float speed;

	glm::vec3 direction;

	//when this reaches zero, kill the bullet
	float lifeTimer;


};