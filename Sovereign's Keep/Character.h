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
	float health;
	float maxHealth;
	float attack;
	float moveSpeed = 1.0;
	//Higher number means they take more damage.
	//Ex. 1.5 means they take 50% more damage for that element.
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
	float currentHealth();
	void restoreHealth(float amt);
	void removeHealth(float amt);
	void fullHeal();
	//GETTER and SETTERS
	void setMoveSpeed(float speed);
	float getMoveSpeed();
	void setPhysicalRES(float amt);
	float getPhysicalRES();
	void setFireRES(float amt);
	float getFireRES();
	void setWaterRES(float amt);
	float getWaterRES();
	void setEarthRES(float amt);
	float getEarthRES();
	void setAirRES(float amt);
	float getAirRES();
	void setElectricityRES(float amt);
	float getElectricityRES();
	void setIceRES(float amt);
	float getIceRES();
};