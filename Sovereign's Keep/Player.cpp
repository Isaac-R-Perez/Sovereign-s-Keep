#include "Player.h"
#include "Basic_Attack.h"

Player::Player(Game* game, int rOrder, int w, int h, int c, std::string path)
	:Character(game, rOrder, w, h, c, path)
{
	glm::mat4 resize = glm::mat4(1.0f);

	resize = glm::scale(glm::mat4(1.0f), glm::vec3(0.0375f, 0.05625f, 0.0f));
	this->setO2W(resize);



	FACING_RIGHT = true;
	FACING_LEFT = false;

	MOVING_UP = false;
	MOVING_DOWN = false;
	MOVING_LEFT = false;
	MOVING_RIGHT = false;
	
	USING_BASIC_ATTACK = false;

	ATTACK_UP = false;
	ATTACK_DOWN = false;
	ATTACK_LEFT = false;
	ATTACK_RIGHT = false;

	CAN_BASIC_ATTACK = true;
	basicAttackCooldown = 0.0f;

	USING_SPELL = false;


}


void Player::update(double dt) {
	
	//printf("x = %f,  y = %f\n", getOrigin().x, getOrigin().y);

	Renderable* spawnedBasicAttack = nullptr;


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

		if (ATTACK_UP) {



			//UPDATE THIS LATER TO ACCOUNT FOR BUFFED BASIC ATTACK COOLDOWN REDUCTION
			basicAttackCooldown = BASE_BASIC_ATTACK_COOLDOWN;
			CAN_BASIC_ATTACK = false;
		}
		else if (ATTACK_RIGHT) {

			spawnedBasicAttack = new Basic_Attack(getGame(), 3, 22, 14, 3, "images/player/basic_attack.png");

			glm::mat4 move = glm::translate(glm::mat4(1.0f), glm::vec3(getOrigin().x, getOrigin().y, 0.0f));

			spawnedBasicAttack->updatePosition(move);


			getGame()->renderableToPendingAdd(spawnedBasicAttack);

			//UPDATE THIS LATER TO ACCOUNT FOR BUFFED BASIC ATTACK COOLDOWN REDUCTION
			basicAttackCooldown = BASE_BASIC_ATTACK_COOLDOWN;
			CAN_BASIC_ATTACK = false;
		}
		else if (ATTACK_DOWN) {

		}
		else if (ATTACK_LEFT) {

		}

	}







	//handle all movement, firing, spell casting, dying, and such logic
	glm::mat4 move = glm::mat4(1.0f);
	glm::vec3 movementVector = glm::vec3(0.0f);

	//camera should be centered on origin of player, unless the player is next to the world border

	glm::vec3 cam;

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

	GLint objectToWorld = glGetUniformLocation(getGame()->getRenderablesProgID(), "objectToWorld");
	if (objectToWorld < 0) printf("couldn't find objectToWorld in shader\n");
	glUniformMatrix4fv(objectToWorld, 1, GL_FALSE, glm::value_ptr(getO2W()));

	glBindTexture(GL_TEXTURE_2D, getTexture());
	glBindVertexArray(getGame()->getVAO());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
