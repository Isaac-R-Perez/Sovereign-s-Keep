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

	//tempory elements in slots
	slottedElements[0] = ELEMENTS::FIRE;
	slottedElements[1] = ELEMENTS::WATER;
	slottedElements[2] = ELEMENTS::EARTH;
	slottedElements[3] = ELEMENTS::AIR;

	resetElementsVector();
	
	currentSpellID = SpellID::None;
	referenceSpell = nullptr;

	setMaxHealth(INITIAL_MAX_HEALTH);
	setMaxMana(INITIAL_MAX_MANA);
	setCurrentMana(INITIAL_MAX_MANA);
	setBaseAttack(10.0f);
	setBaseMoveSpeed(PLAYER_BASE_SPEED);

}


void Player::update(double dt) {
	if (!getCanCollide()) {
		setCanCollide(true);
	}
	//printf("x = %f,  y = %f\n", getOrigin().x, getOrigin().y);

	Renderable* spawnedBasicAttack = nullptr;

	glm::mat4 move = glm::mat4(1.0f);
	glm::vec3 movementVector = glm::vec3(0.0f);
	
	std::multimap<int, Renderable*>::iterator itr;
	std::multimap<int, Renderable*> queue = getGame()->getRenderQueue();
	
	//update hitbox
	getHitBox().updateHitBox(getOrigin(), PLAYER_WIDTH / 1.5f, PLAYER_WIDTH / 1.5f, PLAYER_HEIGHT / 1.5f, PLAYER_HEIGHT / 1.5f);

	//printf("TR: %f %f \n", getHitBox().topRight.x, getHitBox().topRight.y);
	updateEffects(dt);

	//update player's mana
	changeCurrentMana(manaRegenRate * dt);

	getGame()->updateCamera(getOrigin());

	//true if ONE OF THESE IS TRUE
	MOVING = (MOVING_UP || MOVING_RIGHT || MOVING_DOWN || MOVING_LEFT);
	ATTACKING = (ATTACK_LEFT || ATTACK_RIGHT);

	if (CASTING) {
		MOVING = false;
		ATTACKING = false;
	}
	
	if (currentSpellID == SpellID::None) {
		CASTING = false;
	}
	else {
		
			//dont let the player cast if they dont have enough mana
			if (getCurrentMana() < referenceSpell->getManaCost()) {
				//printf("%f\n", getCurrentMana());
				CASTING = false;
			}
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


				
				spawnedBasicAttack = new Basic_Attack(getGame(), 4, static_cast<int>(SPRITE_SHEETS::basic_attack), 0.0f);

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
				
				spawnedBasicAttack = new Basic_Attack(getGame(), 4, static_cast<int>(SPRITE_SHEETS::basic_attack), glm::pi<float>());

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
			
			castingTimer = referenceSpell->getCastTime() / 8.0f; //needs to be tailored to the current spell
			
			
			
			
			current_frame++;

			if (current_frame > CASTING_FRAMES) {
				current_frame = 0;
				CASTING = false;
			}
		}

		if (current_frame == 5 && CAN_CAST_SPELL) {
			//cast the spell
			//printf("Spell id = %d\n", currentSpellID);

			//check if the player has enough mana to cast the spell, then cast

			if (currentSpellID != SpellID::None) {
				
				if (getCurrentMana() > referenceSpell->getManaCost()) {
					
					

					//create a spell to add to the game
					Renderable* castedSpell = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::no_texture), currentSpellID);
					
					getGame()->renderableToPendingAdd(castedSpell);

					spendMana(referenceSpell->getManaCost());
				}

			}

			

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

		move = glm::translate(glm::mat4(1.0f), glm::vec3(movementVector.x * dt * getMoveSpeed(), movementVector.y * dt * getMoveSpeed(), 0.0f));

		updatePosition(move);

	}


	
	//COLLISION CHECK
	if (!queue.empty())
	{
		for (itr = queue.begin(); itr != queue.end(); ) {

			//checks collision with EVERY renderable in the queue
			if (itr->second->getCanCollide() && checkCollision(itr->second)) {
				switch (itr->second->renderOrder) {
				

					case 3: {//enemy
						

						
						printf("PLAYER IS COLLIDING WITH ENEMY\n");
						break;
					}

				}
			}

			++itr;

		}
	}


}


void Player::SavePlayerData()
{
	fstream playerFile;
	// Save player stats to a PlayerData.game
	playerFile.open("PlayerGameData.game", ios::out);
	if (playerFile.is_open())
	{
		//Health/Mana/Souls
		playerFile << getMaxHealth() << endl;
		playerFile << getMaxMana() << endl;
		playerFile << getMonsterSouls() << endl;

		//Base Stats
		playerFile << getBaseAttack() << endl;
		playerFile << getBaseDefense() << endl;
		playerFile << getBaseMoveSpeed() << endl;

		//Element Levels
		playerFile << getFireLevel() << endl;
		playerFile << getWaterLevel() << endl;
		playerFile << getEarthLevel() << endl;
		playerFile << getAirLevel() << endl;
		playerFile << getElectricityLevel() << endl;
		playerFile << getIceLevel() << endl;
		playerFile << getGravityLevel() << endl;

		playerFile.close();
	}
}

void Player::LoadPlayerData()
{
	fstream playerFile;
	// Load player data from PlayerData.game
	playerFile.open("PlayerGameData.game", ios::in);
	if (playerFile.is_open())
	{
		string line;

		//Health/Mana/Souls
		getline(playerFile, line);
		setMaxHealth(stof(line));
		getline(playerFile, line);
		setMaxMana(stof(line));
		getline(playerFile, line);
		setMonsterSouls(stoi(line));

		//Base Stats
		getline(playerFile, line);
		setBaseAttack(stof(line));
		getline(playerFile, line);
		setBaseDefense(stof(line));
		getline(playerFile, line);
		setBaseMoveSpeed(stof(line));

		//Element Levels
		getline(playerFile, line);
		setFireLevel(stoi(line));
		getline(playerFile, line);
		setWaterLevel(stoi(line));
		getline(playerFile, line);
		setEarthLevel(stoi(line));
		getline(playerFile, line);
		setAirLevel(stoi(line));
		getline(playerFile, line);
		setElectricityLevel(stoi(line));
		getline(playerFile, line);
		setIceLevel(stoi(line));
		getline(playerFile, line);
		setGravityLevel(stoi(line));

		playerFile.close();
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


void Player::resetElementsVector() {
	elementsInput.clear();
	elementsInput.emplace_back(ELEMENTS::NONE);
	elementsInput.emplace_back(ELEMENTS::NONE);
	elementsInput.emplace_back(ELEMENTS::NONE);
	inputIterator = 0;
}

void Player::addElementToInputVector(ELEMENTS e) {
	inputIterator = inputIterator % 3;
	elementsInput.at(inputIterator) = e;
	inputIterator++;
}

SpellID Player::combineElements() {

	ELEMENTS tempElements[3];
	tempElements[0] = elementsInput.at(0);
	tempElements[1] = elementsInput.at(1);
	tempElements[2] = elementsInput.at(2);
	resetElementsVector();
	
	/*
		Remove this later, its just for testing
		for (int i = 0; i < 3; i++) {
		printf("Element %d is %d\n", i + 1, tempElements[i]);
	}
	*/
	
	

	/*
		put a bunch of switch statements to determine which spellID to return, which spell needs to be created
	*/

	if (tempElements[0] == ELEMENTS::NONE && tempElements[1] == ELEMENTS::NONE && tempElements[2] == ELEMENTS::NONE)
	{
		return SpellID::None;
	}

	switch (tempElements[0]) {
	//first element is fire	
		case ELEMENTS::FIRE:
		{
			//check if only fire was input
			if (tempElements[1] == ELEMENTS::NONE && tempElements[2] == ELEMENTS::NONE) {
				return SpellID::Fire;
			}

			//only two elements were input
			if (tempElements[2] == ELEMENTS::NONE) {

				switch (tempElements[1]) {
					case ELEMENTS::FIRE: {
						return SpellID::FireFire;
						break;
					}
					
					case ELEMENTS::WATER: {
						return SpellID::FireWater;
						break;
					}
					case ELEMENTS::EARTH: {
						return SpellID::FireEarth;
						break;
					}
					case ELEMENTS::AIR: {
						return SpellID::FireAir;
						break;
					}
									   
				}


			}
			else
			{
				//fire fire ----
				switch (tempElements[1]) {
				case ELEMENTS::FIRE:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireFireFire;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::FireFireWater;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::FireFireEarth;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::FireFireAir;
					}


					break;
				}
				case ELEMENTS::WATER:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireFireWater;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::FireWaterWater;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::FireWaterEarth;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::FireWaterAir;
					}


					break;
				}

				case ELEMENTS::EARTH:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireFireEarth;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::FireWaterEarth;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::FireEarthEarth;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::FireEarthAir;
					}


					break;
				}

				case ELEMENTS::AIR:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireFireAir;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::FireWaterAir;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::FireEarthAir;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::FireAirAir;
					}


					break;
				}
				}
			}

			

			//check for the triple element combos for fire


			break;
		}




		//first element is water
		case ELEMENTS::WATER:
		{
			//check if only fire was input
			if (tempElements[1] == ELEMENTS::NONE && tempElements[2] == ELEMENTS::NONE) {
				return SpellID::Water;
			}

			//only two elements were input
			if (tempElements[2] == ELEMENTS::NONE) {

				switch (tempElements[1]) {
				case ELEMENTS::FIRE: {
					return SpellID::FireWater;
					break;
				}

				case ELEMENTS::WATER: {
					return SpellID::WaterWater;
					break;
				}
				case ELEMENTS::EARTH: {
					return SpellID::WaterEarth;
					break;
				}
				case ELEMENTS::AIR: {
					return SpellID::WaterAir;
					break;
				}

				}


			}
			else
			{
				// ----  ----  ----
				switch (tempElements[1]) {
				case ELEMENTS::FIRE:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireFireWater;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::FireWaterWater;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::FireWaterEarth;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::FireWaterAir;
					}


					break;
				}
				case ELEMENTS::WATER:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireWaterWater;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::WaterWaterWater;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::WaterWaterEarth;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::WaterWaterAir;
					}


					break;
				}

				case ELEMENTS::EARTH:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireWaterEarth;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::WaterWaterEarth;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::WaterEarthEarth;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::WaterEarthAir;
					}


					break;
				}

				case ELEMENTS::AIR:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireWaterAir;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::WaterWaterAir;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::WaterEarthAir;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::WaterAirAir;
					}


					break;
				}
				}
			}



			//check for the triple element combos for fire


			break;
		}



		//first element is Earth	
		case ELEMENTS::EARTH:
		{
			//check if only fire was input
			if (tempElements[1] == ELEMENTS::NONE && tempElements[2] == ELEMENTS::NONE) {
				return SpellID::Earth;
			}

			//only two elements were input
			if (tempElements[2] == ELEMENTS::NONE) {

				switch (tempElements[1]) {
				case ELEMENTS::FIRE: {
					return SpellID::FireEarth;
					break;
				}

				case ELEMENTS::WATER: {
					return SpellID::WaterEarth;
					break;
				}
				case ELEMENTS::EARTH: {
					return SpellID::EarthEarth;
					break;
				}
				case ELEMENTS::AIR: {
					return SpellID::EarthAir;
					break;
				}

				}


			}
			else
			{
				//triple elements
				switch (tempElements[1]) {
				case ELEMENTS::FIRE:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireFireEarth;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::FireWaterEarth;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::FireEarthEarth;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::FireEarthAir;
					}


					break;
				}
				case ELEMENTS::WATER:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireWaterEarth;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::WaterWaterEarth;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::WaterEarthEarth;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::WaterEarthAir;
					}


					break;
				}

				case ELEMENTS::EARTH:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireEarthEarth;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::WaterEarthEarth;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::EarthEarthEarth;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::EarthEarthAir;
					}


					break;
				}

				case ELEMENTS::AIR:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireEarthAir;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::WaterEarthAir;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::EarthEarthAir;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::EarthAirAir;
					}


					break;
				}
				}
			}



			//check for the triple element combos for fire


			break;
		}



		//first element is Air	
		case ELEMENTS::AIR:
		{
			//check if only fire was input
			if (tempElements[1] == ELEMENTS::NONE && tempElements[2] == ELEMENTS::NONE) {
				return SpellID::Air;
			}

			//only two elements were input
			if (tempElements[2] == ELEMENTS::NONE) {

				switch (tempElements[1]) {
				case ELEMENTS::FIRE: {
					return SpellID::FireAir;
					break;
				}

				case ELEMENTS::WATER: {
					return SpellID::WaterAir;
					break;
				}
				case ELEMENTS::EARTH: {
					return SpellID::EarthAir;
					break;
				}
				case ELEMENTS::AIR: {
					return SpellID::AirAir;
					break;
				}

				}


			}
			else
			{
				//fire fire ----
				switch (tempElements[1]) {
				case ELEMENTS::FIRE:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireFireAir;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::FireWaterAir;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::FireEarthAir;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::FireAirAir;
					}


					break;
				}
				case ELEMENTS::WATER:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireWaterAir;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::WaterWaterAir;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::WaterEarthAir;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::WaterAirAir;
					}


					break;
				}

				case ELEMENTS::EARTH:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireEarthAir;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::WaterEarthAir;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::EarthEarthAir;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::EarthAirAir;
					}


					break;
				}

				case ELEMENTS::AIR:
				{
					if (tempElements[2] == ELEMENTS::FIRE) {
						return SpellID::FireAirAir;
					}

					if (tempElements[2] == ELEMENTS::WATER) {
						return SpellID::WaterAirAir;
					}

					if (tempElements[2] == ELEMENTS::EARTH) {
						return SpellID::EarthAirAir;
					}
					if (tempElements[2] == ELEMENTS::AIR) {
						return SpellID::AirAirAir;
					}


					break;
				}
				}
			}



			//check for the triple element combos for fire


			break;
		}

















	}
	

	//IF A SPELL IS NOT IMPLEMENTED YET, the current spell will be kept
	//also if an empty combo is input, the current spell is kept
	return SpellID::None;
}


//this function creates the spell renderable for the player
void Player::setPlayerCurrentSpellID(SpellID i) {
	
	if (i == SpellID::None) {
		// dont change the current spell
		
	}
	else
	{
		if (referenceSpell == nullptr) {
			referenceSpell = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::no_texture), i);
		}

		if (currentSpellID != i) {
			//clear memeory first
			delete referenceSpell;

			//assign new reference spell
			referenceSpell = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::no_texture), i);

			currentSpellID = i;
		}


	}

	
	
}

