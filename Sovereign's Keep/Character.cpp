#include "Character.h"

void Character::statusEffect()
{
	/*
	* This function should be triggered every frame to
	* use the Characters current status's effects
	*/
	if (status.getDuration() > 0.0)
	{
		status.setDuration(-0.1);
		if (status.getDOT() > 0.0)
		{
			removeHealth(status.getDOT());
		}
	}
	else
	{
		status.setNormal();
	}
}

float Character::currentHealth()
{
	return health;
}

void Character::restoreHealth(float amt)
{
	health += amt;
	if (health > maxHealth) {
		health = maxHealth;
	}
}

void Character::removeHealth(float amt)
{
	health -= amt;
	if (health < 0)
	{
		health = 0;
	}
}

void Character::fullHeal()
{
	health = maxHealth;
}

//GETTER and SETTERS

void Character::setMoveSpeed(float speed)
{
	moveSpeed = speed;
}

float Character::getMoveSpeed()
{
	return moveSpeed;
}

void Character::setPhysicalRES(float amt)
{
	physicalRES = amt;
}

float Character::getPhysicalRES()
{
	return physicalRES;
}

void Character::setFireRES(float amt)
{
	fireRES = amt;
}

float Character::getFireRES()
{
	return fireRES;
}

void Character::setWaterRES(float amt)
{
	waterRES = amt;
}

float Character::getWaterRES()
{
	return waterRES;
}

void Character::setEarthRES(float amt)
{
	earthRES = amt;
}

float Character::getEarthRES()
{
	return earthRES;
}

void Character::setAirRES(float amt)
{
	airRES = amt;
}

float Character::getAirRES()
{
	return airRES;
}

void Character::setElectricityRES(float amt)
{
	electricityRES = amt;
}

float Character::getElectricityRES()
{
	return electricityRES;
}

void Character::setIceRES(float amt)
{
	iceRES = amt;
}

float Character::getIceRES()
{
	return iceRES;
}
