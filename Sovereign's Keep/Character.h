#pragma once
#include "Status.h"
/*
* Parent of the Player and Enemy classes
* This will have the common methods and attributes
* between the player and enemy.
*/
class Character
{
private:
	//Character stats
	float maxHealth;
	float currentHealth;
	float baseAttack;
	float currentAttack;
	float baseDefense;
	float currentDefense;
	float baseMoveSpeed = 1.0;
	float currentMoveSpeed;

	//BUFFS/DEBUFFS
	//ATK
	float buffAtk = 0.0;
	float buffAtkTimer = 0.0;
	float debuffAtk = 0.0;
	float debuffAtkTimer = 0.0;

	//DEF
	float buffDef = 0.0;
	float buffDefTimer = 0.0;
	float debuffDef = 0.0;
	float debuffDefTimer = 0.0;

	//SPD
	float buffSpeed = 0.0;
	float buffSpeedTimer = 0.0;
	float debuffSpeed = 0.0;
	float debuffSpeedTimer = 0.0;

	//Higher number means they take more damage.
	//Ex. 1.5 means they take 50% more damage for that element.
	//Fire Damage = enemy.currentAttack * player.fireRES - player.currentDefense
	float physicalRES = 1.0;
	float fireRES = 1.0;
	float waterRES = 1.0;
	float earthRES = 1.0;
	float airRES = 1.0;
	float electricityRES = 1.0;
	float iceRES = 1.0;

public:
	Status status;
	void statusEffect();

	float getCurrentHealth();
	float getMaxHealth();
	void setMaxHealth(float amt);
	void restoreHealth(float amt);
	void removeHealth(float amt);
	void fullHeal();
	
	void buffAttack(float amt, float time);
	void buffMoveSpeed(float amt, float time);

	void setPhysicalRES(float amt);
	void setFireRES(float amt);
	void setWaterRES(float amt);
	void setEarthRES(float amt);
	void setAirRES(float amt);
	void setElectricityRES(float amt);
	void setIceRES(float amt);
	float getPhysicalRES();
	float getFireRES();
	float getWaterRES();
	float getEarthRES();
	float getAirRES();
	float getElectricityRES();
	float getIceRES();
};