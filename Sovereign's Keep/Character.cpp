#include "Character.h"

Character::Character(Game* game, int rOrder, int w, int h, int c, std::string path)
	:Renderable(game, rOrder, w, h, c, path)
{
	atkBuff.reserve(5);
	defBuff.reserve(5);
	spdBuff.reserve(5);
}




void Character::statusEffect()
{
	/*
	* This function should be run every frame of the game.
	* Checks the character's current status and applies the
	* effect while reducing the timer for that status.
	* Will also handle buffs/debuffs.
	*/

	//Here we update the stats
	currentAttack = baseAttack + atkBuffTotal;
	currentDefense = baseDefense + defBuffTotal;
	currentMoveSpeed = baseMoveSpeed + spdBuffTotal;

	/*
	* This section will apply the additonal effects of
	* the current status as well as reduce the time
	* for it. There can only be one status active at a time.
	*/
	if (status.isBurning())
	{
		airRES = 1.5;
		iceRES = 0.5;
	}
	if (status.isWet()) 
	{
		electricityRES = 1.5;
	}
	if (status.isChilled())
	{
		iceRES = 1.5;
		baseMoveSpeed = 0.5;
	}
	if (status.isFrozen())
	{
		earthRES = 1.5;
		currentMoveSpeed = 0.0;
	}
	if (status.isConductive())
	{
		//Empty
	}
	if (status.isStunned())
	{
		currentMoveSpeed = 0.0;
	}
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
	* and remove them when the timer has run out.
	*/

	//ATTACK BUFFS/DEBUFFS
	for (int a = 0; a < atkBuff.size(); a++)
	{
		if (atkBuff[a].time > 0.0f)
		{
			//REDUCE TIME HERE
		}
		else
		{
			atkBuffTotal -= atkBuff[a].amt;
			atkBuff.erase(atkBuff.begin() + a);
			a--;
		}
	}
	atkBuff.shrink_to_fit();

	//DEFENSE BUFFS/DEBUFFS
	for (int d = 0; d < defBuff.size(); d++)
	{
		if (defBuff[d].time > 0.0f)
		{
			//REDUCE TIME HERE
		}
		else
		{
			defBuffTotal -= defBuff[d].amt;
			defBuff.erase(defBuff.begin() + d);
			d--;
		}
	}
	defBuff.shrink_to_fit();

	//SPEED BUFFS/DEBUFFS
	for (int s = 0; s < spdBuff.size(); s++)
	{
		if (spdBuff[s].time > 0.0f)
		{
			//REDUCE TIME HERE
		}
		else
		{
			spdBuffTotal -= spdBuff[s].amt;
			spdBuff.erase(spdBuff.begin() + s);
		}
	}
	spdBuff.shrink_to_fit();
}

float Character::getCurrentHealth()
{
	return currentHealth;
}

void Character::restoreHealth(float amt)
{
	currentHealth += amt;
	if (currentHealth > maxHealth) {
		currentHealth = maxHealth;
	}
}

float Character::getMaxHealth()
{
	return maxHealth;
}

void Character::setMaxHealth(float amt)
{
	maxHealth = amt;
}

void Character::removeHealth(float amt)
{
	currentHealth -= amt;
	if (currentHealth < 0)
	{
		currentHealth = 0;
	}
}

void Character::fullHeal()
{
	currentHealth = maxHealth;
}

/*
* The buff/debuff functions will take in the
* amount to be added or subtracted to the stat
* as well as the time that buff should last.
*/
void Character::buffAttack(float amt, float time)
{
	atkBuff.emplace_back(amt,time);
	atkBuffTotal += amt;
}

void Character::clearAttackBuffs()
{
	atkBuff.clear();
	atkBuffTotal = 0.0f;
}

void Character::buffDefense(float amt, float time)
{
	defBuff.emplace_back(amt, time);
	defBuffTotal += amt;
}

void Character::clearDefenseBuffs()
{
	defBuff.clear();
	defBuffTotal = 0.0f;
}

void Character::buffMoveSpeed(float amt, float time)
{
	spdBuff.emplace_back(amt, time);
	spdBuffTotal += amt;
}

void Character::clearMoveSpeedBuffs()
{
	spdBuff.clear();
	spdBuffTotal = 0.0f;
}

void Character::setPhysicalRES(float amt)
{
	physicalRES = amt;
}

void Character::setFireRES(float amt)
{
	fireRES = amt;
}

void Character::setWaterRES(float amt)
{
	waterRES = amt;
}

void Character::setEarthRES(float amt)
{
	earthRES = amt;
}

void Character::setAirRES(float amt)
{
	airRES = amt;
}

void Character::setElectricityRES(float amt)
{
	electricityRES = amt;
}

void Character::setIceRES(float amt)
{
	iceRES = amt;
}

float Character::getPhysicalRES()
{
	return physicalRES;
}

float Character::getFireRES()
{
	return fireRES;
}

float Character::getWaterRES()
{
	return waterRES;
}

float Character::getEarthRES()
{
	return earthRES;
}

float Character::getAirRES()
{
	return airRES;
}

float Character::getElectricityRES()
{
	return electricityRES;
}

float Character::getIceRES()
{
	return iceRES;
}
