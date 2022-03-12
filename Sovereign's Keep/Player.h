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

const float PLAYER_IDLE_FRAME_TIME = 0.2f;

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

	

	//these are for the arrow key basic attack directions
	
	bool ATTACK_RIGHT;
	bool ATTACK_LEFT;

	bool IDLE;
	bool MOVING;
	bool ATTACKING;
	bool CASTING;
	bool START_NEW_ANIMATION_TIMER;
	bool BEGIN_IDLE;


	//true if the basic attack cooldown is 0.0f
	bool CAN_BASIC_ATTACK;

	

	//time until the player can use another basic attack
	float basicAttackCooldown;

	int idle_frames;
	int attack_frames;
	int walking_frames;
	int casting_frames;

	int current_frame;
	
	float animationTimer;


public:

	Player(Game* g, int rOrder, int defaultSpriteSheet);



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

	
	void setAttackLeft(bool b) { ATTACK_LEFT = b; }
	void setAttackRight(bool b) { ATTACK_RIGHT = b; }

	void setAttacking(bool b) { ATTACKING = b; }
	void setMoving(bool b) { MOVING = b; }
	void setCasting(bool b) { CASTING = b; }


	void render();
	void update(double dt);

};