#pragma once
#include <string>
#include <vector>
using namespace std;
#include "Renderable.h"
#include "Status.h"
/*
* Parent of the Player and Enemy classes
* This will have the common methods and attributes
* between the player and enemy.
*/
class Character : public Renderable
{
private:

	string name;

	//Character stats
	float maxHealth = 100.0f;
	float currentHealth = maxHealth;
	float baseAttack = 20.0f;
	float baseDefense = 10.0f;
	float baseMoveSpeed = 1.0;
	float currentMoveSpeed = 1.0;

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
		Buff(float amt, float time) : amt(amt), time(time) {}
	};

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

	//HEALTH
	float getCurrentHealth() { return currentHealth; }
	float getMaxHealth() { return maxHealth; }
	void setMaxHealth(float amt) { maxHealth = amt; }
	void restoreHealth(float amt);
	void removeHealth(float amt);
	void fullHeal() { currentHealth = maxHealth; }

	//ATTACK
	float getAttack(); //Returns the final calculation after buff/debuff
	float getBaseAttack() { return baseAttack; }
	void setBaseAttack(float amt) { baseAttack = amt; }

	//DEFENSE
	float getDefense();
	float getBaseDefense() { return baseDefense; }
	void setBaseDefense(float amt) { baseDefense = amt; }

	//MOVE SPEED
	float getMoveSpeed();
	float getBaseMoveSpeed() { return baseMoveSpeed; }
	void setBaseMoveSpeed(float amt) { baseMoveSpeed = amt; }

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
};