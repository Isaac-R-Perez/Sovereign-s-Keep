#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(Game* g, int rOrder, int defaultSpriteSheet, EnemyType T)
	:Character(g, rOrder, defaultSpriteSheet)
{
	type = T;
	animationTimer = ENEMY_WALKING_BASE_TIME;


	switch (type) {
		case EnemyType::slime:
		{
			resize(SLIME_WIDTH, SLIME_HEIGHT);
			break;
		}

	
	}

	facingRight = true;
	facingLeft = false;
	current_frame = 0;
	
	//FOR TESTING REMOVE THIS LATER
	glm::mat4 move = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));
	updatePosition(move);
}

/*
	All enemies will just charge the player, but special enemies will have projectiles
	Be sure to flip the enemy when the player is on the left side
*/
void Enemy::update(double dt) {

	if (!getCanCollide()) {
		setCanCollide(true);
	}

	std::multimap<int, Renderable*>::iterator itr;
	std::multimap<int, Renderable*> queue = getGame()->getRenderQueue();
	//Renderable* spawnedBasicAttack = nullptr;

	glm::mat4 move = glm::mat4(1.0f);
	glm::vec3 movementVector = glm::vec3(0.0f);


	if (dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().x > getOrigin().x)
	{
		if (facingLeft) {
			flip();
			facingRight = true;
			facingLeft = false;
		}
	}
	if (dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().x < getOrigin().x)
	{
		if (facingRight) {
			flip();
			facingRight = false;
			facingLeft = true;
		}
	}


	//update hitbox
	switch (type) {
	case EnemyType::slime:
	{
		getHitBox().updateHitBox(getOrigin(), SLIME_WIDTH, SLIME_WIDTH, SLIME_HEIGHT, SLIME_HEIGHT);

		if (current_frame > 2) {
			current_frame = 0;
		}

		break;
	}


	}

	//printf("TR: %f %f \n", getHitBox().topRight.x, getHitBox().topRight.y);


		if (animationTimer > 0.0f) {
			animationTimer -= dt;
		}
		else
		{
			animationTimer = ENEMY_WALKING_BASE_TIME;
			current_frame++;
		}


		//create a vector TOWARDS the player's origin
		movementVector = dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin() - getOrigin();

		movementVector = glm::normalize(movementVector);

		move = glm::translate(glm::mat4(1.0f), glm::vec3(movementVector.x * dt * ENEMY_BASE_SPEED, movementVector.y * dt * ENEMY_BASE_SPEED, 0.0f));

		updatePosition(move);



}

void Enemy::render() {
	float idle_stride = 0.0f;
	float left = 0.0f;
	float right = 0.0f;

	switch (type) {
	case EnemyType::slime:
	{
		idle_stride = 0.25f;

		//put this code in render function???
		setTexture(static_cast<int>(SPRITE_SHEETS::slime));


		left = static_cast<float>((current_frame)*idle_stride);
		left += 0.002f;
		//0.002 is a constant here? without it there is clipping issues...

		right = static_cast<float>((current_frame + 1) * idle_stride);
		right -= 0.002f;

		getGame()->setTextureCoordinates(right, 1.0f,
			right, 0.0f,
			left, 0.0f,
			left, 1.0f);

		break;
	}


	}



	GLint objectToWorld = glGetUniformLocation(getGame()->getRenderablesProgID(), "objectToWorld");
	if (objectToWorld < 0) printf("couldn't find objectToWorld in shader\n");
	glUniformMatrix4fv(objectToWorld, 1, GL_FALSE, glm::value_ptr(getO2W()));

	glBindTexture(GL_TEXTURE_2D, getTexture());
	glBindVertexArray(getGame()->getVAO());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	getGame()->resetTextureCoordinates();


		
}


void Enemy::setSoulDrop(int amt)
{
	soulDrop = amt;
}

int Enemy::getSoulDrop()
{
	return soulDrop;
}
