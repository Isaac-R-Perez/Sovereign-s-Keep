#pragma once
#include "Character.h"
/*
* Child of the Character class.
* This class is for all enemy types that the
* game will have.
*/
class Enemy: public Character
{
private:
	int soulDrop = 1; //The amount of souls the enemy will drop
public:
	void setSoulDrop(int amt);
	int getSoulDrop();
};

