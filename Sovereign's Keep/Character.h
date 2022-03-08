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
	float maxHealth;
	float currentHealth;
	float baseAttack;
	float baseDefense;
	float moveSpeed = 1.0;

	struct Buff
	{
		float amt, time;
		Buff(float amt, float time) : amt(amt), time(time)
		{
		}
	};
	vector<Buff> atkBuff;
	vector<Buff> defBuff;
	vector<Buff> spdBuff;

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

	Character(Game* game, int rOrder, int w, int h, int c, std::string path);

	
	Status status;
	void statusEffect();

	float getCurrentHealth();
	float getMaxHealth();
	void setMaxHealth(float amt);
	void restoreHealth(float amt);
	void removeHealth(float amt);
	void fullHeal();

	float getAttack(); //Returns the final calculation after buff/debuff
	float getBaseAttack();
	void setBaseAttack(float amt);
	float getDefense();
	float getBaseDefense();
	void setBaseDefense(float amt);
	float getMoveSpeed();
	
	void buffAttack(float amt, float time);
	void clearAttackBuffs();
	void buffDefense(float amt, float time);
	void clearDefenseBuffs();
	void buffMoveSpeed(float amt, float time);
	void clearMoveSpeedBuffs();

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