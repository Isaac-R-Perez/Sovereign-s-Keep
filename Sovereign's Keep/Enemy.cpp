#include "Enemy.h"
#include "Player.h"
#include <random>

Enemy::Enemy(Game* g, int rOrder, int defaultSpriteSheet, EnemyType T, stats s)
	:Character(g, rOrder, defaultSpriteSheet)
{
	type = T;

	//damagedBy.clear();


	//remove this when level manager is done
	switch (type) {
		case EnemyType::slime:
		{
			resize(SLIME_WIDTH, SLIME_HEIGHT);
			animationTimer = SLIME_TIMER;
			break;
		}
		case EnemyType::bat:
		{
			resize(BAT_WIDTH, BAT_HEIGHT);
			animationTimer = BAT_TIMER;
			break;
		}
		case EnemyType::crab:
		{
			resize(CRAB_WIDTH, CRAB_HEIGHT);
			animationTimer = CRAB_TIMER;
			break;
		}
		case EnemyType::minotaur:
		{
			resize(MINOTAUR_WIDTH, MINOTUAR_HEIGHT);
			animationTimer = MINOTAUR_TIMER;
			break;
		}
		case EnemyType::skull:
		{
			resize(SKULL_WIDTH, SKULL_HEIGHT);
			animationTimer = SKULL_TIMER;
			break;
		}

	}

	setBaseHealth(s.h);
	setCurrentHealth(s.h);
	setBaseMaxHealth(s.mh);
	setCurrentMaxHealth(s.mh);
	setBaseAttack(s.a);
	setCurrentAttack(s.a);
	setBaseDefense(s.d);
	setCurrentDefense(s.d);
	setBaseMoveSpeed(s.s);
	setCurrentMoveSpeed(s.s);

	enemyStats = s;

	//this sets the size of the enemy to the size of the renderable's width and height
	

	
	facingRight = true;
	facingLeft = false;
	current_frame = 0;
	
	//FOR TESTING REMOVE THIS LATER
	//glm::mat4 move = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));
	//updatePosition(move);


	glm::vec3 knockbackDirection = glm::vec3(1.0f);

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


	updateEffects(dt);

	applySpellBuffs();


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


	//the direction of the last knockback is what the enemy travels in
	bool knockback = searchSpellBuff(SpellID::knockback);
	
	
	
	

	if (!stunned && !frozen) {

		if (animationTimer > 0.0f) {
			animationTimer -= dt;
		}
		else
		{


			switch (type) {
			case EnemyType::slime:
			{


				animationTimer = SLIME_TIMER;

				break;
			}
			case EnemyType::bat:
			{

				animationTimer = BAT_TIMER;

				break;
			}
			case EnemyType::crab:
			{

				animationTimer = CRAB_TIMER;


				break;
			}
			case EnemyType::minotaur:
			{
				std::uniform_real_distribution<float> dis(0.0f, 0.02f);

				animationTimer = MINOTAUR_TIMER + dis(getGame()->getNumberEngine());


				break;
			}
			case EnemyType::skull:
			{
				animationTimer = SKULL_TIMER;


				break;
			}

			}
			
			
			
			current_frame++;
		}




		switch (type) {
		case EnemyType::slime:
		{


			if (current_frame > 2) {
				current_frame = 0;
			}

			break;
		}
		case EnemyType::bat:
		{


			if (current_frame > 3) {
				current_frame = 0;
			}

			break;
		}
		case EnemyType::crab:
		{


			if (current_frame > 5) {
				current_frame = 0;
			}

			break;
		}
		case EnemyType::minotaur:
		{


			if (current_frame > 3) {
				current_frame = 0;
			}

			break;
		}
		case EnemyType::skull:
		{


			if (current_frame > 2) {
				current_frame = 0;
			}

			break;
		}

		}

		if (knockback) {
			//create a vector TOWARDS the player's origin
			movementVector = knockbackDirection;

			//movementVector = glm::normalize(movementVector);

			move = glm::translate(glm::mat4(1.0f), glm::vec3(movementVector.x * dt * getCurrentMoveSpeed() * 0.85f, movementVector.y * dt * getCurrentMoveSpeed() * 0.85f, 0.0f));

			//ADD this back when testing is done

			updatePosition(move);
		}
		else
		{

			//create a vector TOWARDS the player's origin
			movementVector = dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin() - getOrigin();

			movementVector = glm::normalize(movementVector);

			move = glm::translate(glm::mat4(1.0f), glm::vec3(movementVector.x * dt * getCurrentMoveSpeed(), movementVector.y * dt * getCurrentMoveSpeed(), 0.0f));

			//ADD this back when testing is done

			updatePosition(move);
		}


	}
	else if (frozen) {



		//also set GUI flag for blue tint
		if (knockback) {
			//create a vector TOWARDS the player's origin
			movementVector = knockbackDirection;

			//movementVector = glm::normalize(movementVector);

			move = glm::translate(glm::mat4(1.0f), glm::vec3(movementVector.x * dt * getCurrentMoveSpeed() * 0.5f, movementVector.y * dt * getCurrentMoveSpeed() * 0.5f, 0.0f));

			//ADD this back when testing is done

			updatePosition(move);
		}

	}
	else if (stunned) {



		if (knockback) {
			//create a vector TOWARDS the player's origin
			movementVector = knockbackDirection;

			//movementVector = glm::normalize(movementVector);

			move = glm::translate(glm::mat4(1.0f), glm::vec3(movementVector.x * dt * getCurrentMoveSpeed() * 0.7f, movementVector.y * dt * getCurrentMoveSpeed() * 0.7f, 0.0f));

			//ADD this back when testing is done

			updatePosition(move);
		}



	}
	


	
	
	
	
	
	
	getHitBox().updateHitBox(getOrigin(), getWidth(), getWidth(), getHeight(), getHeight());







	//printf("TR: %f %f \n", getHitBox().topRight.x, getHitBox().topRight.y);



		setHealthLastFrame(getCurrentHealth());

		if (getCurrentHealth() <= 0.0f)
		{
			kill();
		}

		//add these function to player as well
		//clearDamagedBy();

		//printf("%d\n", damagedBy.size());

}

void Enemy::render() {
	float idle_stride = 0.0f;
	float left = 0.0f;
	float right = 0.0f;

	if (frozen) {
		getGame()->setGUIFlag(-2);
	}

	if (getHealthLastFrame() - getCurrentHealth() >= 1.0f) {
		//took more than 1 damage, so flash red for one frame
		getGame()->setGUIFlag(-1);
	}

	switch (type) {
	case EnemyType::slime:
	{
		idle_stride = 0.25f;
		break;
	}
	case EnemyType::bat:
	{
		idle_stride = static_cast<float>(1.0f / 4.0f);
		break;
	}
	case EnemyType::crab:
	{
		idle_stride = static_cast<float>(1.0f / 6.0f);
		break;
	}
	case EnemyType::minotaur:
	{
		idle_stride = static_cast<float>(1.0f / 4.0f);
		break;
	}
	case EnemyType::skull:
	{
		idle_stride = static_cast<float>(1.0f / 4.0f);
		break;
	}


	}

	left = static_cast<float>((current_frame)*idle_stride);
	left += 0.002f;
	//0.002 is a constant here? without it there is clipping issues...

	right = static_cast<float>((current_frame + 1) * idle_stride);
	right -= 0.002f;

	getGame()->setTextureCoordinates(right, 1.0f,
		right, 0.0f,
		left, 0.0f,
		left, 1.0f);

	GLint objectToWorld = glGetUniformLocation(getGame()->getRenderablesProgID(), "objectToWorld");
	if (objectToWorld < 0) printf("couldn't find objectToWorld in shader\n");
	glUniformMatrix4fv(objectToWorld, 1, GL_FALSE, glm::value_ptr(getO2W()));

	glBindTexture(GL_TEXTURE_2D, getTexture());
	glBindVertexArray(getGame()->getVAO());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	getGame()->resetTextureCoordinates();


	getGame()->setGUIFlag(0);
		
}


void Enemy::setSoulDrop(int amt)
{
	soulDrop = amt;
}

int Enemy::getSoulDrop()
{
	return soulDrop;
}

const float MUD_SLOW = 0.5f;
const float AIR_SPIKE_SLOW = 0.75f;

//all buffs are searched and all stats are calculated for this frame
void Enemy::applySpellBuffs() {

	int amt = 0;

	setCurrentMoveSpeed(getBaseMoveSpeed());

	setCurrentDefense(getBaseDefense());

	setCurrentAttack(getBaseAttack());

	stunned = false;
	frozen = false;


	//set all current stats to the BASE stats for this enemy
	if (searchSpellBuff(SpellID::WaterEarth)) {
		setCurrentMoveSpeed(getCurrentMoveSpeed() * MUD_SLOW);
	}

	if (searchSpellBuff(SpellID::EarthEarth) || searchSpellBuff(SpellID::FireEarthEarth)) {
		stunned = true;
	}

	if (searchSpellBuff(SpellID::FireWaterAir)) {
		frozen = true;
	}

	amt = buffAmount(SpellID::EarthAir);
	if (amt > 0) {
		for (int i = 0; i < amt; i++) {
			setCurrentMoveSpeed(getCurrentMoveSpeed() * AIR_SPIKE_SLOW);
		}
	}

}

//Called from the Game::SpawnEnemy() function.
void Enemy::WaveBuff(int wave)
{
	//Percentage based
	float hpBuff = 0.0f;
	float atkBuff = 0.0f;
	float defBuff = 0.0f;
	float speedBuff = 0.0f;

	

	hpBuff = (static_cast<float>(wave) * 0.20f); //10% per wave
	atkBuff = (static_cast<float>(wave) * 0.075f); //5% per wave
	defBuff = (static_cast<float>(wave) * 0.075f); //7.5% per wave
	speedBuff = (static_cast<float>(wave) * 0.1f); //6% per wave

	setBaseMaxHealth(getBaseMaxHealth() + (getBaseMaxHealth() * hpBuff));
	setCurrentHealth(getCurrentHealth() + (getCurrentHealth() * hpBuff));

	setBaseHealth(getBaseMaxHealth() + (getBaseMaxHealth() * hpBuff));
	setCurrentHealth(getCurrentHealth() + (getCurrentHealth() * hpBuff));

	setBaseAttack(getBaseAttack() + (getBaseAttack() * atkBuff));
	setCurrentAttack(getCurrentAttack() + (getCurrentAttack() * atkBuff));

	setBaseDefense(getBaseDefense() + (getBaseDefense() * defBuff));
	setCurrentDefense(getCurrentDefense() + (getCurrentDefense() * defBuff));

	setBaseMoveSpeed(getBaseMoveSpeed() + (getBaseMoveSpeed() * speedBuff));
	setCurrentMoveSpeed(getCurrentMoveSpeed() + (getCurrentMoveSpeed() * speedBuff));
}
