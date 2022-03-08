#pragma once
#include "Character.h"
/*
* Child of the Character class.
* This class is for any specific methods that only apply
* to the player. Such as movement, attacking, casting spells, etc.
*/

/*
	CONSTANTS
*/
const int MAX_MONSTER_SOULS = 999;
const int INITIAL_MAX_MANA = 100;

const float PLAYER_BASE_SPEED = 0.3f;
const float BASE_BASIC_ATTACK_COOLDOWN = 0.2f;

class Player: public Character
{
private:
	int monsterSouls; //Stores the monster souls collected during the run.

	float maxMana;
	float currentMana;

	bool FACING_RIGHT;
	bool FACING_LEFT;
	bool MOVING_UP;
	bool MOVING_DOWN;
	bool MOVING_RIGHT;
	bool MOVING_LEFT;

	//true if an arrow key is pressed
	bool USING_BASIC_ATTACK;

	//these are for the arrow key basic attack directions
	bool ATTACK_UP;
	bool ATTACK_DOWN;
	bool ATTACK_RIGHT;
	bool ATTACK_LEFT;


	//true if the basic attack cooldown is 0.0f
	bool CAN_BASIC_ATTACK;

	//true if the player has enough mana to cast the current active spell and the key to cast the spell is pressed
	bool USING_SPELL;

	//time until the player can use another basic attack
	float basicAttackCooldown;



public:

	Player(Game* game, int rOrder, int w, int h, int c, std::string path);



	//SOULS
	void setSouls(int amt);
	void addSouls(int amt);
	void spendSouls(int amt);
	int getSouls();

	//MANA
	void setMaxMana(float amt);
	float getMaxMana();
	void setCurrentMana(float amt);
	float getCurrentMana();
	bool spendMana(float amt);


	void setFacingRight(bool b) { FACING_RIGHT = b; }
	void setFacingLeft(bool b) { FACING_LEFT = b; }
	void setMovingUp(bool b) { MOVING_UP = b; }
	void setMovingDown(bool b) { MOVING_DOWN = b; }
	void setMovingLeft(bool b) { MOVING_LEFT = b; }
	void setMovingRight(bool b) { MOVING_RIGHT = b; }

	void setAttackUp(bool b) { ATTACK_UP = b; }
	void setAttackDown(bool b) { ATTACK_DOWN = b; }
	void setAttackLeft(bool b) { ATTACK_LEFT = b; }
	void setAttackRight(bool b) { ATTACK_RIGHT = b; }


	void render();
	void update(double dt);

};