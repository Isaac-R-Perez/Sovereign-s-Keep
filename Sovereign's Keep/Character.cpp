#include "Character.h"

Character::Character(Game* g, int rOrder, int defaultSpriteSheet)
	:Renderable(g, rOrder, defaultSpriteSheet)
{
	
}


void Character::updateEffects(float dt)
{
	/*
	* This function should be run every frame of the game.
	* Checks the character's current status and applies the
	* effect while reducing the timer for that status.
	* Will also handle buffs/debuffs.
	*/

	currentMoveSpeed = getMoveSpeed();

	//STATUS DURATION
	if (status.getDuration() > 0.0)
	{
		status.setDuration(status.getDuration() - dt);
	}
	else
	{
		status.setNormal();
	}

	/*
	* This section will handle the buffs and debuffs
	* and remove them from the vector when their timer has run out.
	*/

	updateBuff(atkBuff, dt);
	updateBuff(defBuff, dt);
	updateBuff(spdBuff, dt);

	updateBuff(fireDMGBuff, dt);
	updateBuff(waterDMGBuff, dt);
	updateBuff(earthDMGBuff, dt);
	updateBuff(airDMGBuff, dt);
	updateBuff(electricityDMGBuff, dt);
	updateBuff(iceDMGBuff, dt);

	updateBuff(fireRESBuff, dt);
	updateBuff(waterRESBuff, dt);
	updateBuff(earthRESBuff, dt);
	updateBuff(airRESBuff, dt);
	updateBuff(electricityRESBuff, dt);
	updateBuff(iceRESBuff, dt);
}

void Character::updateBuff(vector<Buff>& buff,float dt)
{
	for (int i = 0; i < buff.size(); i++) 
	{
		if (buff[i].time > 0.0f)
		{
			//REDUCE TIME
			buff[i].time -= dt;
		}
		else
		{
			//Remove buff from array
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
		return baseMoveSpeed + buffTotal;
	}
}