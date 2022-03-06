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

	int maxMana = 100;
	int currentMana = maxMana;
public:
	//SOULS
	void setSouls(int amt);
	void addSouls(int amt);
	void spendSouls(int amt);
	int getSouls();

	//MANA
	void setMaxMana(int amt);
	int getMaxMana();
	void setCurrentMana(int amt);
	int getCurrentMana();
	bool spendMana(int amt);
};