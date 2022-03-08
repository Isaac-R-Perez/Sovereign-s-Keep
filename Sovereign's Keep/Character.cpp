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

float Character::getAttack()
{
	float buffTotal = 0.0f;
	for (int i = 0; i < atkBuff.size(); i++)
	{
		buffTotal += atkBuff[i].amt;
	}
	return baseAttack + buffTotal;
}

float Character::getBaseAttack()
{
	return baseAttack;
}

void Character::setBaseAttack(float amt)
{
	baseAttack = amt;
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

float Character::getBaseDefense()
{
	return baseDefense;
}

void Character::setBaseDefense(float amt)
{
	baseDefense = amt;
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

/*
* The buff/debuff functions will take in the
* amount to be added or subtracted to the stat
* as well as the time that buff should last.
*/
void Character::buffAttack(float amt, float time)
{
	atkBuff.emplace_back(amt,time);
}

void Character::clearAttackBuffs()
{
	atkBuff.clear();
}

void Character::buffDefense(float amt, float time)
{
	defBuff.emplace_back(amt, time);
}

void Character::clearDefenseBuffs()
{
	defBuff.clear();
}

void Character::buffMoveSpeed(float amt, float time)
{
	spdBuff.emplace_back(amt, time);
}

void Character::clearMoveSpeedBuffs()
{
	spdBuff.clear();
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
