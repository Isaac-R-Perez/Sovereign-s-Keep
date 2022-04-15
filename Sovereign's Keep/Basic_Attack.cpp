#include "Basic_Attack.h"

Basic_Attack::Basic_Attack(Game* g, int rOrder, int defaultSpriteSheet, float ang)
	:Renderable(g, rOrder, defaultSpriteSheet) {

	resize(BULLET_WIDTH, BULLET_HEIGHT);


	damage = BASE_DAMAGE;
	speed = BULLET_BASE_SPEED;
	angle = ang;
	direction = glm::vec3(1.0f, 0.0f, 0.0f); //points down x axis initially

	if (angle != 0.0f) {
		
		//rotate the texture to render at the correct angle
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
		updatePosition(rotation);

		//rotate direction to match given angle
		direction =  rotation * glm::vec4(direction, 0.0f);

		//normalize new direction
		direction = glm::normalize(direction);
	}
	
	lifeTimer = BULLET_LIFETIME;

}

Basic_Attack::Basic_Attack(Game* g, int rOrder, int defaultSpriteSheet, float ang, float speedModifier)
	:Renderable(g, rOrder, defaultSpriteSheet) {

	resize(BULLET_WIDTH, BULLET_HEIGHT);


	damage = BASE_DAMAGE;
	speed = BULLET_BASE_SPEED * speedModifier;
	angle = ang;
	direction = glm::vec3(1.0f, 0.0f, 0.0f); //points down x axis initially

	if (angle != 0.0f) {

		//rotate the texture to render at the correct angle
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
		updatePosition(rotation);

		//rotate direction to match given angle
		direction = rotation * glm::vec4(direction, 0.0f);

		//normalize new direction
		direction = glm::normalize(direction);
	}

	lifeTimer = BULLET_LIFETIME;

}


void Basic_Attack::update(double dt) {
	if (!getCanCollide()) {
		setCanCollide(true);
	}
	
	std::multimap<int, Renderable*>::iterator itr;
	std::multimap<int, Renderable*> queue = getGame()->getRenderQueue();

	getHitBox().updateHitBox(getOrigin(), BULLET_HEIGHT / 1.6f, BULLET_HEIGHT / 1.6f, BULLET_HEIGHT / 1.6f, BULLET_HEIGHT / 1.6f);

	
	glm::mat4 move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * dt * speed, direction.y * dt * speed, 0.0f));
	
	updatePosition(move);



	//COLLISION CHECK
	if (!queue.empty())
	{
		for (itr = queue.begin(); itr != queue.end(); ) {

			//checks collision with EVERY renderable in the queue
			if (itr->second->getCanCollide() && checkCollision(itr->second)) {
				switch (itr->second->renderOrder) {


				case 3: {//enemy

					//need to process the hit here and calculate bullet damage done to the enemy
					float playerAttack = dynamic_cast<Player*>(getGame()->getPlayer())->getBaseAttack();
					float enemyDefense = dynamic_cast<Enemy*>(itr->second)->getBaseDefense();
					dynamic_cast<Enemy*>(itr->second)->alterHealth(-(playerAttack - enemyDefense));
					dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.2f, SpellID::knockback));
					dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(direction);
					kill();

					printf("Bullet IS COLLIDING WITH Enemy\n");
					break;
				}

				}
			}

			++itr;

		}
	}



	lifeTimer -= dt;

	if (lifeTimer < 0.0f) {
		kill();
	}



}

void Basic_Attack::render() {

	GLint objectToWorld = glGetUniformLocation(getGame()->getRenderablesProgID(), "objectToWorld");
	if (objectToWorld < 0) printf("couldn't find objectToWorld in shader\n");
	glUniformMatrix4fv(objectToWorld, 1, GL_FALSE, glm::value_ptr(getO2W()));

	glBindTexture(GL_TEXTURE_2D, getTexture());
	glBindVertexArray(getGame()->getVAO());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}