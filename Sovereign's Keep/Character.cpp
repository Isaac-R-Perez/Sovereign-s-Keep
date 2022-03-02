#include "Character.h"

void Character::statusEffect()
{
	/*
	* This function should be run every frame of the game.
	* Checks the character's current status and applies the
	* effect while reducing the timer for that status.
	* Will also handle buffs/debuffs.
	*/

	//Here we update the stats
	currentAttack = baseAttack + buffAtk;
	currentDefense = baseDefense + buffDef;
	currentMoveSpeed = baseMoveSpeed + buffSpeed;

	if (status.isBurning())
	{
		airRES = 1.5;
		iceRES = 0.5;
	}
	if (status.isWet()) 
	{
		electricityRES = 1.5;
	}
	if (status.isChilled())
	{
		iceRES = 1.5;
	}
	if (status.isFrozen())
	{
		earthRES = 1.5;
	}
	if (status.isConductive())
	{

	}
	if (status.isStunned())
	{

	}
}

float Character::getCurrentHealth()
{
	return currentHealth;
}

void Character::restoreHealth(float amt)
{
	currentHealth += amt;
	if (currentHealth > maxHealth) {
		currentHealth = maxHealth;
	}
}

float Character::getMaxHealth()
{
	return maxHealth;
}

void Character::setMaxHealth(float amt)
{
	maxHealth = amt;
}

void Character::removeHealth(float amt)
{
	currentHealth -= amt;
	if (currentHealth < 0)
	{
		currentHealth = 0;
	}
}

void Character::fullHeal()
{
	currentHealth = maxHealth;
}

void Character::setPhysicalRES(float amt)
{
	physicalRES = amt;
}

void Character::setFireRES(float amt)
{
	fireRES = amt;
}

void Character::setWaterRES(float amt)
{
	waterRES = amt;
}

void Character::setEarthRES(float amt)
{
	earthRES = amt;
}

void Character::setAirRES(float amt)
{
	airRES = amt;
}

void Character::setElectricityRES(float amt)
{
	electricityRES = amt;
}

void Character::setIceRES(float amt)
{
	iceRES = amt;
}

float Character::getPhysicalRES()
{
	return physicalRES;
}

float Character::getFireRES()
{
	return fireRES;
}

float Character::getWaterRES()
{
	return waterRES;
}

float Character::getEarthRES()
{
	return earthRES;
}

float Character::getAirRES()
{
	return airRES;
}

float Character::getElectricityRES()
{
	return electricityRES;
}

float Character::getIceRES()
{
	return iceRES;
}
