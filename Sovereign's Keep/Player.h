#pragma once
#include "Character.h"
/*
* Child of the Character class.
* This class is for any specific methods that only apply
* to the player.
*/
class Player: public Character
{
private:
	int monsterSouls; //Stores the monster souls collected during the run.
	int maxMonsterSouls = 999;
public:
	void setSouls(int amt);
	void addSouls(int amt);
	void removeSouls(int amt);
	int getSouls();
};