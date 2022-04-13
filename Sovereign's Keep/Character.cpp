#include "Character.h"

Character::Character(Game* g, int rOrder, int defaultSpriteSheet)
	:Renderable(g, rOrder, defaultSpriteSheet)
{
	//set all initial base stats
}


void Character::updateEffects(float dt)
{
	/*
	* This function should be run every frame of the game.
	* Checks the character's current status and applies the
	* effect while reducing the timer for that status.
	* Will also handle buffs/debuffs.
	*/

	currentMoveSpeed = getMoveSpeed(); //getMoveSpeed() will check if Frozen or Stunned.

	//STATUS DURATION
	if (status.getDuration() > 0.0)
	{
		status.setDuration(status.getDuration() - dt);
		removeHealth(status.getDOT());
	}
	else
	{
		removeStatus();
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

/*
* updateBuff only looks to see if the time for that buff has run out.
* Once it sees that the time is under 0, it will remove that buff from its vector.
*/
void Character::updateBuff(vector<Buff>& buff,float dt)
{
	for (int i = 0; i < buff.size(); i++) 
	{
		if (buff[i].noTimeLimit == false)
		{
			if (buff[i].time > 0.0f)
			{
				//Reduce Time by dt
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
	if (currentHealth < 0.0f)
	{
		currentHealth = 0.0f;
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

void Character::removeStatus()
{
	status.setNormal();

	fireRES = 1.0f;
	waterRES = 1.0f;
	earthRES = 1.0f;
	airRES = 1.0f;
	electricityRES = 1.0f;
	iceRES = 1.0f;
}

void Character::inflictBurning()
{
	if (status.isWet())
	{
		removeStatus();
		return;
	}
	if (status.isChilled())
	{
		removeStatus();
		return;
	}
	if (status.isFrozen())
	{
		removeStatus();
		return;
	}
	if (status.isStunned())
	{
		//If Stunned, then change nothing.
		return;
	}
	if (status.isConductive())
	{
		//Remove Conductive, then continue to apply burning in its place
		removeStatus();
	}
	if (status.isBurning())
	{
		if (status.getDuration() < status.getBurningDuration() * 3)
		{
			status.setDuration(status.getDuration() + 2.0f);
		}
	}
	else
	{
		status.setBurning();
		airRES = 1.5f;
	}
}

void Character::inflictWet()
{
	if (status.isBurning())
	{
		removeStatus();
		return;
	}
	if (status.isChilled())
	{
		removeStatus();
		inflictFrozen();
		return;
	}
	if (status.isFrozen())
	{
		return;
	}
	if (status.isConductive())
	{
		removeStatus();
		inflictStunned();
		return;
	}
	if (status.isStunned())
	{
		return;
	}
	if (status.isWet())
	{
		if (status.getDuration() < status.getWetDuration() * 3)
		{
			status.setDuration(status.getDuration() + 2.0f);
		}
	}
	else
	{
		status.setWet();
		electricityRES = 1.5f;
	}
}

void Character::inflictChilled()
{
	if (status.isBurning())
	{
		removeStatus();
		return;
	}
	if (status.isWet())
	{
		removeStatus();
		inflictFrozen();
		return;
	}
	if (status.isFrozen())
	{
		return;
	}
	if (status.isConductive())
	{
		removeStatus();
	}
	if (status.isStunned())
	{
		return;
	}
	if (status.isChilled())
	{
		if (status.getDuration() < status.getChilledDuration() * 3)
		{
			status.setDuration(status.getDuration() + 2.0f);
		}
	}
	else
	{
		status.setChilled();
		iceRES = 1.5f;
	}
}

void Character::inflictFrozen()
{
	if (status.isFrozen())
	{
		if (status.getDuration() < status.getFrozenDuration() * 3)
		{
			status.setDuration(status.getDuration() + 2.0f);
		}
	}
	else
	{
		removeStatus();
		status.setFrozen();
		earthRES = 1.5f;
	}
}

void Character::inflictConductive()
{
	if (status.isBurning())
	{
		removeStatus();
		return;
	}
	if (status.isWet())
	{
		removeStatus();
		inflictStunned();
		return;
	}
	if (status.isChilled())
	{
		removeStatus();
		return;
	}
	if (status.isFrozen())
	{
		return;
	}
	if (status.isStunned())
	{
		return;
	}
	if (status.isConductive())
	{
		if (status.getDuration() < status.getConductiveDuration() * 3)
		{
			status.setDuration(status.getDuration() + 2.0f);
		}
	}
	else
	{
		status.setConductive();
		electricityRES = 1.5f;
	}
}

void Character::inflictStunned()
{
	if (status.isStunned())
	{
		if (status.getDuration() < status.getStunnedDuration() * 3)
		{
			status.setDuration(status.getDuration() + 2.0f);
		}
	}
	else
	{
		removeStatus();
		status.setStunned();
		electricityRES = 1.5f;
	}
}
