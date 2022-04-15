#pragma once
#include <string>
#include <vector>
#include "Renderable.h"
#include "Status.h"
#include "Spell.h"
using namespace std;
/*
* Parent of the Player and Enemy classes
* This will have the common methods and attributes
* between the player and enemy.
*/



struct spellBuff {
	//how the long the buff will last on the character
	float duration;

	//which spell applied the buff
	SpellID spellID;

	//true if buff should be removed
	bool done;

	spellBuff(float d, SpellID s) {
		duration = d;
		spellID = s;
		done = false;

	}

	//on update, reduce the duration timer based on frameTime
	void update(double dt) {
		duration -= dt;

		if (duration <= 0.0f) {
			done = true;
		}

	}


};


class Character : public Renderable
{
private:

	string name;

	//Character stats



	/*
		USE THESE WITH THE WAVE MANAGER TO SET BASE STATS
		THESE BASE STATS WILL BE SET IN THE CONSTRUCTOR
	*/
	float baseHealth;
	float baseMaxHealth;
	float baseAttack;
	float baseDefense;
	float baseMoveSpeed;


	/*
		USE THESE FOR ALL OTHER PURPOSES
		These will be set every frame to the above set base stats
	*/
	float currentMaxHealth;
	float currentHealth;
	float currentMoveSpeed;
	float currentDefense;
	float currentAttack;


	//a buff as applied this, so stop animation, and set movespeed to 0.0 until stun buff is gone
	bool stunned;

	//a buff as applied this, so stop animation, SET RENDER FLAG TO frozen (blue shifted), and set movespeed to 0.0 until frozen buff is gone
	bool frozen;


	//saves the value of this character's health from the last frame
	float healthLastFrame = 0.0f;

	//Element Damage Multipliers
	float fireDMG = 1.0;
	float waterDMG = 1.0;
	float earthDMG = 1.0;
	float airDMG = 1.0;
	float electricityDMG = 1.0;
	float iceDMG = 1.0;

	//Ex. 1.5 means they take 50% more damage for that element.
	//Enemy Fire Damage Hitting Player = enemy.getAttack() * player.getFireRES() - player.getDefense()
	float fireRES = 1.0;
	float waterRES = 1.0;
	float earthRES = 1.0;
	float airRES = 1.0;
	float electricityRES = 1.0;
	float iceRES = 1.0;

	struct Buff
	{
		float amt, time;
		bool noTimeLimit = false;
		Buff(float amt, float time) : amt(amt), time(time) {}
		Buff(float amt) : amt(amt) 
		{
			//Second constructor for buffs with no expire time.
			time = 0.0f;
			noTimeLimit = true;
		}
	};



	//holds all of the buffs that the character currently has
	vector<spellBuff> buffs;




	vector<Buff> atkBuff;
	vector<Buff> defBuff;
	vector<Buff> spdBuff;

	vector<Buff> fireDMGBuff;
	vector<Buff> waterDMGBuff;
	vector<Buff> earthDMGBuff;
	vector<Buff> airDMGBuff;
	vector<Buff> electricityDMGBuff;
	vector<Buff> iceDMGBuff;

	vector<Buff> fireRESBuff;
	vector<Buff> waterRESBuff;
	vector<Buff> earthRESBuff;
	vector<Buff> airRESBuff;
	vector<Buff> electricityRESBuff;
	vector<Buff> iceRESBuff;

public:

	Character(Game* g, int rOrder, int defaultSpriteSheet);
	
	Status status;
	void updateEffects(float dt);
	void updateBuff(vector<Buff>& buff,float dt);


	/*
	float baseMoveSpeed;

	
		USE THESE FOR ALL OTHER PURPOSES
		These will be set every frame to the above set base stats

	float currentMoveSpeed;
	*/


	//HEALTH
	float getCurrentHealth() { return currentHealth; }
	float getCurrentMaxHealth() { return currentMaxHealth; }
	float getBaseHealth() { return baseHealth; }
	float getBaseMaxHealth() { return baseMaxHealth; }

	void setCurrentHealth(float amt) { currentHealth = amt; }
	void setCurrentMaxHealth(float amt) { currentMaxHealth = amt; }
	void setBaseHealth(float h) { baseHealth = h; }
	void setBaseMaxHealth(float h) { baseMaxHealth = h; }

	void setHealthLastFrame(float h) { healthLastFrame = h; }
	float getHealthLastFrame() { return healthLastFrame; }

	//send a positive number to heal, a negative to deal damage
	void alterHealth(float amt);

	void fullHeal() { currentHealth = currentMaxHealth; }

	//ATTACK
	//float getAttack(); //Returns the final calculation after buff/debuff
	float getBaseAttack() { return baseAttack; }
	float getCurrentAttack() { return currentAttack; }

	void setBaseAttack(float amt) { baseAttack = amt; }
	void setCurrentAttack(float a) { currentAttack = a; }


	//DEFENSE
	//float getDefense();
	float getBaseDefense() { return baseDefense; }
	float getCurrentDefense() { return currentDefense; }

	void setBaseDefense(float amt) { baseDefense = amt; }
	void setCurrentDefense(float d) { currentDefense = d; }

	//MOVE SPEED
	//float getMoveSpeed();


	//sets the current movespeed for the character (needed to apply buffs/debuffs to the character directly)
	void setBaseMoveSpeed(float s) { baseMoveSpeed = s; }
	void setCurrentMoveSpeed(float s) { currentMoveSpeed = s; }

	float getBaseMoveSpeed() { return baseMoveSpeed; }
	float getCurrentMoveSpeed() { return currentMoveSpeed; }


	//ELEMENT DAMAGE
	void setFireDMG(float amt) { fireDMG = amt; }
	void setWaterDMG(float amt) { waterDMG = amt; }
	void setEarthDMG(float amt) { earthDMG = amt; }
	void setAirDMG(float amt) { airDMG = amt; }
	void setElectricityDMG(float amt) { airDMG = amt; }
	void setIceDMG(float amt) { iceDMG = amt; }
	float getFireDMG() { return fireDMG; }
	float getWaterDMG() { return waterDMG; }
	float getEarthDMG() { return earthDMG; }
	float getAirDMG() { return airDMG; }
	float getElectricityDMG() { return electricityDMG; }
	float getIceDMG() { return iceDMG; }

	//RESISTANCE
	void setFireRES(float amt) { fireRES = amt; }
	void setWaterRES(float amt) { waterRES = amt; }
	void setEarthRES(float amt) { earthRES = amt; }
	void setAirRES(float amt) { airRES = amt; }
	void setElectricityRES(float amt) { electricityRES = amt; }
	void setIceRES(float amt) { iceRES = amt; }
	float getFireRES() { return fireRES; }
	float getWaterRES() { return waterRES; }
	float getEarthRES() { return earthRES; }
	float getAirRES() { return airRES; }
	float getElectricityRES() { return electricityRES; }
	float getIceRES() { return iceRES; }

	//Status Effects
	void removeStatus();
	void inflictBurning();
	void inflictWet();
	void inflictChilled();
	void inflictFrozen();
	void inflictConductive();
	void inflictStunned();

	/*
	* BUFFS AND DEBUFFS
	*/
	
	//Stat buffs/debuffs (Just pass in a negative number to debuff)
	void buffAttack(float amt, float time) { atkBuff.emplace_back(amt, time); }
	void buffDefense(float amt, float time) { defBuff.emplace_back(amt, time); }
	void buffMoveSpeed(float amt, float time) { spdBuff.emplace_back(amt, time); }
	void clearAttackBuffs() { atkBuff.clear(); }
	void clearDefenseBuffs() { defBuff.clear(); }
	void clearMoveSpeedBuffs() { spdBuff.clear(); }

	//Element damage buffs/debuffs
	void buffFireDamage(float amt, float time) { fireDMGBuff.emplace_back(amt, time); }
	void buffWaterDamage(float amt, float time) { waterDMGBuff.emplace_back(amt, time); }
	void buffEarthDamage(float amt, float time) { earthDMGBuff.emplace_back(amt, time); }
	void buffAirDamage(float amt, float time) { airDMGBuff.emplace_back(amt, time); }
	void buffElectricityDamage(float amt, float time) { electricityDMGBuff.emplace_back(amt, time); }
	void buffIceDamage(float amt, float time) { iceDMGBuff.emplace_back(amt, time); }
	void clearFireDamageBuffs() { fireDMGBuff.clear(); }
	void clearWaterDamageBuffs() { waterDMGBuff.clear(); }
	void clearEarthDamageBuffs() { earthDMGBuff.clear(); }
	void clearAirDamageBuffs() { airDMGBuff.clear(); }
	void clearElectricityDamageBuffs() { electricityDMGBuff.clear(); }
	void clearIceDamageBuffs() { iceDMGBuff.clear(); }

	//Element resistance buffs/debuffs
	void buffFireResistance(float amt, float time) { fireRESBuff.emplace_back(amt, time); }
	void buffWaterResistance(float amt, float time) { waterRESBuff.emplace_back(amt, time); }
	void buffEarthResistance(float amt, float time) { earthRESBuff.emplace_back(amt, time); }
	void buffAirResistance(float amt, float time) { airRESBuff.emplace_back(amt, time); }
	void buffElectricityResistance(float amt, float time) { electricityRESBuff.emplace_back(amt, time); }
	void buffIceResistance(float amt, float time) { iceRESBuff.emplace_back(amt, time); }
	void clearFireResistanceBuffs() { fireRESBuff.clear(); }
	void clearWaterResistanceBuffs() { waterRESBuff.clear(); }
	void clearEarthResistanceBuffs() { earthRESBuff.clear(); }
	void clearAirResistanceBuffs() { airRESBuff.clear(); }
	void clearElectricityResistanceBuffs() { electricityRESBuff.clear(); }
	void clearIceResistanceBuffs() { iceRESBuff.clear(); }




	void addBuff(spellBuff b) { buffs.emplace_back(b); }

	//returns the buffs vector (use for searching the vector for buffs)
	vector<spellBuff>& getBuffs() { return buffs; }

	//searches the buff vector at certain index, returns true if found
	bool hasBuff(SpellID s, int i);


	//searches the vector and returns how many of that spell's buff is in it
	int buffAmount(SpellID spell);


	void updateSpellBuffs(double dt);


	//search the buffs vector and return true at the first instance of the spellID
	bool searchSpellBuff(SpellID s);

	//removes the FIRST INSTANCE of the buff, only removes one of the given buff
	void removeSpellBuff(SpellID s);



};