#include "Player.h"
#include "Basic_Attack.h"

Player::Player(Game* g, int rOrder, int defaultSpriteSheet)
	:Character(g, rOrder, defaultSpriteSheet)
{
	resize(PLAYER_WIDTH, PLAYER_HEIGHT);

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

	CAN_BASIC_ATTACK = false;
	basicAttackCooldown = 0.0f;

	START_ATTACKING = true;
	LOOP_FORWARD = true;

	CAN_CAST_SPELL = true;

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

	
	//update hitbox
	getHitBox().updateHitBox(getOrigin(), PLAYER_WIDTH, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_HEIGHT);



	getGame()->updateCamera(getOrigin());

	//true if ONE OF THESE IS TRUE
	MOVING = (MOVING_UP || MOVING_RIGHT || MOVING_DOWN || MOVING_LEFT);
	ATTACKING = (ATTACK_LEFT || ATTACK_RIGHT);

	if (CASTING) {
		MOVING = false;
		ATTACKING = false;
	}
	

	if (MOVING && ATTACKING) {
		//player is current moving with WASD, so set animation to walking
		//even if the player is attacking, the walking animation overrides this, but player will attack slower

		animationState = states::attacking;

	}
	else if (ATTACKING) {
		//if the player is just attacking and standing still
		animationState = states::attacking;
		
	}
	else if (MOVING) {
		animationState = states::walking;
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
		}



		if (START_ATTACKING) {
			current_frame = 0;
			LOOP_FORWARD = true;
			START_ATTACKING = false;
		}

		


		if (LOOP_FORWARD) {

			if (attackingTimer > 0.0f) {
				attackingTimer -= dt;
			}
			else
			{
				current_frame++;

				if (current_frame > 9)
				{
					current_frame = 3;
				}
				attackingTimer = PLAYER_ATTACKING_FRAME_TIME;
			}

			

		}

		

		if (basicAttackCooldown == 0.0f) {
			if (current_frame == 3)
			{
				CAN_BASIC_ATTACK = true;
			}
			if (current_frame == 7) {
				CAN_BASIC_ATTACK = true;
			}
		}


		//player can attack so check which direction to fire
		if (CAN_BASIC_ATTACK) {


			if (ATTACK_RIGHT) {


				
				spawnedBasicAttack = new Basic_Attack(getGame(), 3, static_cast<int>(SPRITE_SHEETS::basic_attack));

				glm::mat4 move = glm::translate(glm::mat4(1.0f), glm::vec3(getOrigin().x, getOrigin().y, 0.0f));

				spawnedBasicAttack->updatePosition(move);


				getGame()->renderableToPendingAdd(spawnedBasicAttack);
				
				

				

				//UPDATE THIS LATER TO ACCOUNT FOR BUFFED BASIC ATTACK COOLDOWN REDUCTION

				if (MOVING) {
					basicAttackCooldown = PLAYER_ATTACKING_FRAME_TIME;
				}
				else {
					basicAttackCooldown = PLAYER_ATTACKING_FRAME_TIME * 0.52f; //double shot when not moving
				}


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
		//play walking animation based on the direction the player is facing
		

		if (castingTimer > 0.0f) {
			castingTimer -= dt;
		}
		else
		{
			castingTimer = PLAYER_CASTING_FRAME_TIME; //needs to be tailored to the current spell
			current_frame++;

			if (current_frame > CASTING_FRAMES) {
				CASTING = false; //stop casting
				current_frame = 0;
			}
		}

		if (current_frame == 5 && CAN_CAST_SPELL) {
			//cast the spell
			//printf("Spell was cast!\n");
			CAN_CAST_SPELL = false;
		}

	}



	if (MOVING) {

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



}

void Player::render() {

	float idle_stride = 0.0f;
	float left = 0.0f; //x value
	float right = 0.0f; //x value
	float up = 0.0f;
	
	
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
		idle_stride = 0.1f; // (1/10)  450x35


		//scale the player so that they are the same size as the idle animation!!!
		

		//put this code in render function???
		setTexture(static_cast<int>(SPRITE_SHEETS::player_attacking));


		if (current_frame == 0) {
			left = static_cast<float>((current_frame*idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.055555f;
			right -= 0.002f;

			up = 0.742857f;
			scale(ATTACK_SCALE_START_X, ATTACK_SCALE_START_Y);
		}

		if (current_frame == 1) {
			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.055555f;
			right -= 0.002f;

			up = 0.771428f;
			scale(ATTACK_SCALE_START_X, ATTACK_SCALE_START_Y);
		}

		if (current_frame == 2) {
			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.048888f;
			right -= 0.002f;

			up = 0.942857f;
			scale(ATTACK_SCALE_START_X, ATTACK_SCALE_START_Y);
		}

		if (current_frame == 3) {
			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.011111f;
			right -= 0.002f;

			up = 0.82857f;
			scale(ATTACK_SCALE_START_X, ATTACK_SCALE_START_Y);
		}

		if (current_frame == 4) {
			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.017777f;
			right -= 0.002f;

			up = 0.6f;
			scale(ATTACK_SCALE_START_X, ATTACK_SCALE_START_Y);
		}

		if (current_frame == 5) {
			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.031111f;
			right -= 0.002f;

			up = 0.62857f;
			scale(ATTACK_SCALE_START_X, ATTACK_SCALE_START_Y);
		}

		if (current_frame == 6) {
			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.026666f;
			right -= 0.002f;

			up = 0.65714f;
			scale(ATTACK_SCALE_START_X, ATTACK_SCALE_START_Y);

		}

		if (current_frame == 7) {
			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.0f;
			right -= 0.002f;

			up = 1.0f;
			scale(ATTACK_SCALE_END_X, ATTACK_SCALE_END_Y);
		}

		if (current_frame == 8) {
			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.022222f;
			right -= 0.002f;

			up = 0.971428f;
			scale(ATTACK_SCALE_END_X, ATTACK_SCALE_END_Y);

		}

		if (current_frame == 9) {
			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.028888f;
			right -= 0.002f;

			up = 0.971428f;
			scale(ATTACK_SCALE_END_X, ATTACK_SCALE_END_Y);

		}


		getGame()->setTextureCoordinates(right, up,
			right, 0.0f,
			left, 0.0f,
			left, up);
	}
	else if (animationState == states::casting) {
	//scale the player so that they are the same size as the idle animation!!!
		scale(CAST_SCALE, 1.0f);

		idle_stride = 0.125f; // (1/8)

		//put this code in render function???
		setTexture(static_cast<int>(SPRITE_SHEETS::player_casting));


		if (current_frame == 0) {
			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.049107f;
			right -= 0.002f;
		}

		if (current_frame == 1) {
			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.0446428f;
			right -= 0.002f;

		}

		if (current_frame == 2) {
			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.0133928f;
			right -= 0.002f;

		}

		if (current_frame == 3) {
			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.03125f;
			right -= 0.002f;

		}

		if (current_frame == 4) {
			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.0267857f;
			right -= 0.002f;

		}

		if (current_frame == 5) {


			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.0133928f;
			right -= 0.002f;

		}

		if (current_frame == 6) {

			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.0f;
			right -= 0.002f;


		}

		if (current_frame == 7) {
			left = static_cast<float>((current_frame * idle_stride));
			left += 0.002f;

			right = static_cast<float>((current_frame + 1) * idle_stride) - 0.0446428f;
			right -= 0.002f;

		}

		getGame()->setTextureCoordinates(right, 1.0f,
			right, 0.0f,
			left, 0.0f,
			left, 1.0f);
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

	//reset the character size SAFELY!!!
	if (animationState == states::walking || animationState == states::attacking || animationState  == states::casting) {
		if (FACING_LEFT) {
			resize(PLAYER_WIDTH, PLAYER_HEIGHT);
			flip();
		}
		else
		{
			resize(PLAYER_WIDTH, PLAYER_HEIGHT);
		}
	}

}


void Player::addMonsterSouls(int amt)
{
	monsterSouls += amt;
	if (monsterSouls > MAX_MONSTER_SOULS)
	{
		monsterSouls = MAX_MONSTER_SOULS;
	}
}

void Player::spendMonsterSouls(int amt)
{
	monsterSouls -= amt;
	if (monsterSouls < 0)
	{
		monsterSouls = 0;
	}
}

bool Player::spendMana(float amt)
{
	if (amt < Mana)
	{
		//Returns true if the player can cast the spell
		Mana -= amt;
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
