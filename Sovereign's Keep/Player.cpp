#include "Player.h"
#include "Basic_Attack.h"

Player::Player(Game* g, int rOrder, int defaultSpriteSheet)
	:Character(g, rOrder, defaultSpriteSheet)
{
	glm::mat4 resize = glm::mat4(1.0f);

	resize = glm::scale(glm::mat4(1.0f), glm::vec3(0.0275f, 0.0725f, 0.0f));
	this->setO2W(resize);



	IDLE = true;
	MOVING = false;
	ATTACKING = false;
	CASTING = false;

	FACING_RIGHT = true;
	FACING_LEFT = false;

	MOVING_UP = false;
	MOVING_DOWN = false;
	MOVING_LEFT = false;
	MOVING_RIGHT = false;

	START_NEW_ANIMATION_TIMER = true;
	IDLE = true;

	ATTACK_LEFT = false;
	ATTACK_RIGHT = false;

	CAN_BASIC_ATTACK = true;
	basicAttackCooldown = 0.0f;


	animationTimer = 0.0f;
	idleTimer = PLAYER_IDLE_FRAME_TIME;
	walkingTimer = PLAYER_WALKING_FRAME_TIME;
	attackingTimer = PLAYER_ATTACKING_FRAME_TIME;
	castingTimer = PLAYER_CASTING_FRAME_TIME;

	current_frame = 0;

	animationState = states::idling;

}


void Player::update(double dt) {
	
	//printf("x = %f,  y = %f\n", getOrigin().x, getOrigin().y);

	Renderable* spawnedBasicAttack = nullptr;

	glm::mat4 move = glm::mat4(1.0f);
	glm::vec3 movementVector = glm::vec3(0.0f);

	//camera should be centered on origin of player, unless the player is next to the world border
	glm::vec3 cam;

	//true if ONE OF THESE IS TRUE
	MOVING = (MOVING_UP || MOVING_RIGHT || MOVING_DOWN || MOVING_LEFT);
	ATTACKING = (ATTACK_LEFT || ATTACK_RIGHT);

	if (MOVING || MOVING && ATTACKING) {
		//player is current moving with WASD, so set animation to walking
		//even if the player is attacking, the walking animation overrides this, but player will attack slower

		animationState = states::walking;

	}
	else if (ATTACKING) {
		//if the player is just attacking and standing still
		animationState = states::attacking;
		
	}
	else if (CASTING) {
		//player is just initiated a spell, so STOP MOVEMENT AND DO NOT LET PLAYER ATTACK
		animationState = states::casting;
	}
	else {
		animationState = states::idling;
	}
	

	if (animationState == states::idling)
	{
		//play idle animation
		if (current_frame > IDLE_FRAMES) {
			current_frame = 0;
		}

		if (idleTimer > 0.0f) {
			idleTimer -= dt;
		}
		else
		{
			idleTimer = PLAYER_IDLE_FRAME_TIME;
			current_frame++;

			if (current_frame > IDLE_FRAMES) {
				current_frame = 0;
			}
		}




	}
	else if (animationState == states::attacking)
	{
		//play attack animation, loop until a new action is performed, ONLY SPAWN BULLETS WHEN A "SPAWN FRAME" is reached for the first time in a loop

		if (basicAttackCooldown > 0.0f && !CAN_BASIC_ATTACK) {
			basicAttackCooldown -= dt;
		}
		else
		{
			basicAttackCooldown = 0.0f;
			CAN_BASIC_ATTACK = true;
		}


		//player can attack so check which direction to fire
		if (CAN_BASIC_ATTACK) {


			if (ATTACK_RIGHT) {


				//update this
				/*
				spawnedBasicAttack = new Basic_Attack(getGame(), 3, 22, 14, 3, "images/player/basic_attack.png");

				glm::mat4 move = glm::translate(glm::mat4(1.0f), glm::vec3(getOrigin().x, getOrigin().y, 0.0f));

				spawnedBasicAttack->updatePosition(move);


				getGame()->renderableToPendingAdd(spawnedBasicAttack);
				
				*/

				

				//UPDATE THIS LATER TO ACCOUNT FOR BUFFED BASIC ATTACK COOLDOWN REDUCTION
				basicAttackCooldown = BASE_BASIC_ATTACK_COOLDOWN;
				CAN_BASIC_ATTACK = false;
			}
			else if (ATTACK_LEFT) {

			}

		}



	}
	else if (animationState == states::walking)
	{
		//play walking animation based on the direction the player is facing
		if (current_frame > WALKING_FRAMES) {
			current_frame = 0;
		}

		if (walkingTimer > 0.0f) {
			walkingTimer -= dt;
		}
		else
		{
			walkingTimer = PLAYER_WALKING_FRAME_TIME;
			current_frame++;

			if (current_frame > WALKING_FRAMES) {
				current_frame = 0;
			}
		}



	}
	else if (animationState == states::casting) {

		//play the casting animation and cast the current spell

	}





	if (MOVING_UP) {
		movementVector.y += (1920.0f / 1080.0f);

	}

	if (MOVING_DOWN) {
		movementVector.y -= (1920.0f / 1080.0f);
	}

	if (MOVING_RIGHT) {
		movementVector.x += 1.0f;
	}
	if (MOVING_LEFT) {
		movementVector.x -= 1.0f;
	}

	glm::normalize(movementVector);

	move = glm::translate(glm::mat4(1.0f), glm::vec3(movementVector.x * dt * PLAYER_BASE_SPEED, movementVector.y * dt * PLAYER_BASE_SPEED, 0.0f));

	updatePosition(move);



}

void Player::render() {

	float idle_stride = 0.0f;
	float left = 0.0f;
	float right = 0.0f;
	
	
	if (animationState == states::idling) {

		idle_stride = 0.25f;

		//put this code in render function???
		setTexture(static_cast<int>(SPRITE_SHEETS::player_idle));


		left = static_cast<float>((current_frame) * idle_stride);
		left += 0.002f;
		//0.002 is a constant here? without it there is clipping issues...

		right = static_cast<float>((current_frame + 1) * idle_stride);
		right -= 0.002f;

		getGame()->setTextureCoordinates(right, 1.0f,
										 right, 0.0f,
										 left, 0.0f,
										 left, 1.0f);
	}
	else if (animationState == states::walking)
	{
		
		//scale the player so that they are the same size as the idle animation!!!
		scale(1.45f, 1.0f);

		idle_stride = 0.166666f; // (1/6)

		//put this code in render function???
		setTexture(static_cast<int>(SPRITE_SHEETS::player_walking));


		left = static_cast<float>((current_frame)*idle_stride);
		left += 0.002f;
		//0.002 is a constant here? without it there is clipping issues...

		right = static_cast<float>((current_frame + 1) * idle_stride);
		right -= 0.002f;

		getGame()->setTextureCoordinates(right, 1.0f,
			right, 0.0f,
			left, 0.0f,
			left, 1.0f);
		

	}
	else if (animationState == states::attacking) {

	}
	else if (animationState == states::casting) {

	}
	else
	{
		//put this code in render function???
		setTexture(static_cast<int>(SPRITE_SHEETS::player_default));
	}
	




	GLint objectToWorld = glGetUniformLocation(getGame()->getRenderablesProgID(), "objectToWorld");
	if (objectToWorld < 0) printf("couldn't find objectToWorld in shader\n");
	glUniformMatrix4fv(objectToWorld, 1, GL_FALSE, glm::value_ptr(getO2W()));

	glBindTexture(GL_TEXTURE_2D, getTexture());
	glBindVertexArray(getGame()->getVAO());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	getGame()->resetTextureCoordinates();

	if (animationState == states::walking) {

		//undo the scale
		scale(static_cast<float>(1.0f/1.45f), 1.0f);
		//floating point drift??????
	}

}


void Player::setSouls(int amt)
{
	monsterSouls = amt;
}

void Player::addSouls(int amt)
{
	monsterSouls += amt;
	if (monsterSouls > MAX_MONSTER_SOULS)
	{
		monsterSouls = MAX_MONSTER_SOULS;
	}
}

void Player::spendSouls(int amt)
{
	monsterSouls -= amt;
	if (monsterSouls < 0)
	{
		monsterSouls = 0;
	}
}

int Player::getSouls()
{
	return monsterSouls;
}

void Player::setMaxMana(float amt)
{
	maxMana = amt;
}

float Player::getMaxMana()
{
	return maxMana;
}

void Player::setCurrentMana(float amt)
{
	currentMana = amt;
}

float Player::getCurrentMana()
{
	return currentMana;
}

bool Player::spendMana(float amt)
{
	if (amt < currentMana)
	{
		//Returns true if the player can cast the spell
		currentMana -= amt;
		return true;
	}
	else
	{
		//Returns false if the player can not cast the spell
		return false;
	}
}

void Player::scale(float xScale, float yScale) {
	glm::mat4 scale = getO2W() * glm::scale(glm::mat4(1.0f), glm::vec3(xScale, yScale, 0.0f));
	setO2W(scale);
}

void Player::flip() {

	//apply a negative scale to the player's matrix as well as the 4 points of their hit box
	glm::mat4 inverted = getO2W() * glm::scale(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, 0.0f));
	setO2W(inverted);
}