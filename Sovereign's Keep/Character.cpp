#include "Character.h"

Character::Character(Game* game, int rOrder, int w, int h, int c, std::string path)
	:Renderable(game, rOrder, w, h, c, path)
{
	
}


void Character::statusEffect()
{
	/*
	* This function should be run every frame of the game.
	* Checks the character's current status and applies the
	* effect while reducing the timer for that status.
	* Will also handle buffs/debuffs.
	*/

	//STATUS DURATION
	if (status.getDuration() > 0.0)
	{
		//REDUCE DURATION HERE
	}
	else
	{
		status.setNormal();
	}

	/*
	* This section will handle the buffs and debuffs
	* and remove them from the vector when their timer has run out.
	*/

	updateBuff(atkBuff);
	updateBuff(defBuff);
	updateBuff(spdBuff);

	updateBuff(fireDMGBuff);
	updateBuff(waterDMGBuff);
	updateBuff(earthDMGBuff);
	updateBuff(airDMGBuff);
	updateBuff(electricityDMGBuff);
	updateBuff(iceDMGBuff);

	updateBuff(fireRESBuff);
	updateBuff(waterRESBuff);
	updateBuff(earthRESBuff);
	updateBuff(airRESBuff);
	updateBuff(electricityRESBuff);
	updateBuff(iceRESBuff);
}

void Character::updateBuff(vector<Buff>& buff)
{
	for (int i = 0; i < buff.size(); i++) 
	{
		if (buff[i].time > 0.0f)
		{
			//REDUCE TIME HERE
			//buff[i].time -= TIME;
		}
		else
		{
			buff.erase(buff.begin() + i);
			i--;
		}
		buff.shrink_to_fit();
	}
}

void Character::restoreHealth(float amt)
{
	currentHealth += amt;
	if (currentHealth > maxHealth) {
		currentHealth = maxHealth;
	}
}

void Character::removeHealth(float amt)
{
	currentHealth -= amt;
	if (currentHealth < 0)
	{
		currentHealth = 0;
	}
}

float Character::getAttack()
{
	float buffTotal = 0.0f;
	for (int i = 0; i < atkBuff.size(); i++)
	{
		buffTotal += atkBuff[i].amt;
	}
	return baseAttack + buffTotal;
}

float Character::getDefense()
{
	float buffTotal = 0.0f;
	for (int i = 0; i < defBuff.size(); i++)
	{
		buffTotal += defBuff[i].amt;
	}
	return baseDefense + buffTotal;
}

float Character::getMoveSpeed()
{
	if (status.isFrozen() || status.isStunned())
	{
		return 0.0;
	}
	else
	{
		float buffTotal = 0.0f;
		for (int i = 0; i < spdBuff.size(); i++)
		{
			buffTotal += spdBuff[i].amt;
		}
		return moveSpeed + buffTotal;
	}
}