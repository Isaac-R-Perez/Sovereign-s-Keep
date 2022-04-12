#pragma once
#include "Character.h"
#include "Game.h"
#include "Spell.h"
#include <fstream>
/*
* Child of the Character class.
* This class is for any specific methods that only apply
* to the player. Such as movement, attacking, casting spells, etc.
*/

/*
	CONSTANTS
*/
const int MAX_MONSTER_SOULS = 999;
const float INITIAL_MAX_MANA = 100.0f;
const float INITIAL_MAX_HEALTH = 100.0f;

const float PLAYER_BASE_SPEED = 0.3f;
const float BASE_BASIC_ATTACK_COOLDOWN = 0.3f; //this is unused as the FRAME TIME determines attack speed

const float PLAYER_IDLE_FRAME_TIME = 0.55f;
const float PLAYER_WALKING_FRAME_TIME = 0.1f;
const float PLAYER_ATTACKING_FRAME_TIME = 0.08f; //max attack speed is 0.016, double shot does not work at this speed...
const float PLAYER_CASTING_FRAME_TIME = 0.125f; //1 full second! 8 * 0.125 = 1


const int IDLE_FRAMES = 3;
const int ATTACK_FRAMES = 9;
const int WALKING_FRAMES = 5;
const int CASTING_FRAMES = 7;


const float ATTACK_SCALE_START_X = 1.2f;
const float ATTACK_SCALE_START_Y = 1.0f;

const float ATTACK_SCALE_END_X = 1.5;
const float ATTACK_SCALE_END_Y = 1.25f;

const float CAST_SCALE = 1.15f;

const float PLAYER_HEIGHT = 0.0725f;
const float PLAYER_WIDTH = 0.0275f;

const int MAX_ELEMENT_LEVEL = 3; //The max level any element can be.

class Player : public Character
{
private:
	int monsterSouls; //Stores the monster souls collected during the run.

	float maxMana;
	float Mana;
	float manaRegenRate = 0.1f;

	//Element Levels
	int FireLevel = 1;
	int WaterLevel = 1;
	int EarthLevel = 1;
	int AirLevel = 1;
	int ElectricityLevel = 1;
	int IceLevel = 1;
	int GravityLevel = 1;

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
	bool CAN_CAST_SPELL;
	bool START_ATTACKING;
	bool LOOP_FORWARD;

	//time until the player can use another basic attack
	float basicAttackCooldown;


	int current_frame;

	float animationTimer;
	float idleTimer;
	float walkingTimer;
	float attackingTimer;
	float castingTimer;


	//use the enum to track this
	int animationState;

	ELEMENTS slottedElements[4];

	std::vector<ELEMENTS> elementsInput;
	int inputIterator;


	SpellID currentSpellID;

	//use this to get the info about the currentSpell the player has
	Spell* referenceSpell;


public:

	enum states {
		idling, walking, attacking, casting
	};

	Player(Game* g, int rOrder, int defaultSpriteSheet);

	//SOULS
	void setMonsterSouls(int amt) { monsterSouls = amt; }
	void addMonsterSouls(int amt);
	void spendMonsterSouls(int amt);
	int getMonsterSouls() { return monsterSouls; }

	//MANA
	void setMaxMana(float amt) { maxMana = amt; }
	float getMaxMana() { return maxMana; }
	void setCurrentMana(float amt) { Mana = amt; }
	float getCurrentMana() { return Mana; }
	bool spendMana(float amt);
	void setManaRegenRate(float amt) { manaRegenRate = amt; }
	float getManaRegenRate() { return manaRegenRate; }

	//ELEMENT LEVELS
	void setFireLevel(int level) { FireLevel = level; }
	void setWaterLevel(int level) { WaterLevel = level; }
	void setEarthLevel(int level) { EarthLevel = level; }
	void setAirLevel(int level) { AirLevel = level; }
	void setElectricityLevel(int level) { ElectricityLevel = level; }
	void setIceLevel(int level) { IceLevel = level; }
	void setGravityLevel(int level) { GravityLevel = level; }
	int getFireLevel() { return FireLevel; }
	int getWaterLevel() { return WaterLevel; }
	int getEarthLevel() { return EarthLevel; }
	int getAirLevel() { return AirLevel; }
	int getElectricityLevel() { return ElectricityLevel; }
	int getIceLevel() { return IceLevel; }
	int getGravityLevel() { return GravityLevel; }


	void setFacingRight(bool b) { FACING_RIGHT = b; }
	void setFacingLeft(bool b) { FACING_LEFT = b; }
	void setMovingUp(bool b) { MOVING_UP = b; }
	void setMovingDown(bool b) { MOVING_DOWN = b; }
	void setMovingLeft(bool b) { MOVING_LEFT = b; }
	void setMovingRight(bool b) { MOVING_RIGHT = b; }


	void setAttackLeft(bool b) { ATTACK_LEFT = b; }
	void setAttackRight(bool b) { ATTACK_RIGHT = b; }

	void setAttacking(bool b) { ATTACKING = b; }
	void setStartAttacking(bool b) { START_ATTACKING = b; }
	void setMoving(bool b) { MOVING = b; }
	void setCasting(bool b) { CASTING = b; }

	//Player Data
	void SavePlayerData();
	void LoadPlayerData();

	//run this function everytime a player presses Q, AND CAN CAST THE SPELL
	void resetCastingVariables() {
		current_frame = 0; //make sure the animation start at the beginning
		CAN_CAST_SPELL = true;
	}

	bool getFacingRight() { return FACING_RIGHT; }
	bool getFacingLeft() { return FACING_LEFT; }
	bool getAttackingLeft() { return ATTACK_LEFT; }
	bool getAttackingRight() { return ATTACK_RIGHT; }
	bool getMovingLeft() { return MOVING_LEFT; }
	bool getMovingRight() { return MOVING_RIGHT; }

	bool getCasting() { return CASTING; }
	bool getCanCastSpell() { return CAN_CAST_SPELL; }

	void render();
	void update(double dt);

	

	void scale(float xScale, float yScale);

	ELEMENTS getElementFromSlot(int i) { return slottedElements[i]; }
	
	void addElementToInputVector(ELEMENTS e);
	
	void resetElementsVector();
	SpellID combineElements();

	void setPlayerCurrentSpellID(SpellID i);
	


};