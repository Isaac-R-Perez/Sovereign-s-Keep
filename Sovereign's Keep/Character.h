#pragma once
#include "Renderable.h"
/*
* Parent of the Player and Enemy classes
* This will have the common methods and attributes
* between the player and enemy.
*/
class Character : public Renderable
{
private:
	int health;
	float attack;
	float moveSpeed;
public:
	//Higher number means they take more damage.
	//Ex. 1.5 means they take 50% more damage for that element.
	float physicalRES = 1.0;
	float fireRES = 1.0;
	float waterRES = 1.0;
	float earthRES = 1.0;
	float airRES = 1.0;
	float electricityRES = 1.0;
	float iceRES = 1.0;
};

