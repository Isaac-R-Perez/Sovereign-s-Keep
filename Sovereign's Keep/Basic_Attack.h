#pragma once
#include "Renderable.h"
/*
	This class will handle all logic related to the player's basic attack, including bullet spawnpoints and modifiers
*/

const float BULLET_BASE_SPEED = 0.6f;
const float BASE_DAMAGE = 20.0f;


class Basic_Attack : public Renderable {

public:

	Basic_Attack(Game* game, int rOrder, int w, int h, int c, std::string path);

	void render();
	void update(double dt);


private:

	//holds the angle that the basic attack flys
	float angle;

	float damage;

	float speed;

	glm::vec3 direction;


};