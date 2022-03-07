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

	//Here we update the stats
	currentAttack = baseAttack + buffAtk - debuffAtk;
	currentDefense = baseDefense + buffDef - debuffDef;
	currentMoveSpeed = baseMoveSpeed + buffSpeed - debuffSpeed;

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
	//ATTACK
	if (buffAtkTimer > 0.0)
	{
		//REDUCE buffAtkTimer HERE
	}
	else
	{
		buffAtkTimer = 0.0;
		buffAtk = 0.0;
	}
	//DEFENSE
	if (buffDefTimer > 0.0)
	{
		//REDUCE buffDefTimer HERE
	}
	else
	{
		buffDefTimer = 0.0;
		buffDef = 0.0;
	}
	//SPEED
	if (buffSpeedTimer > 0.0)
	{
		//REDUCE buffSpeedTimer HERE
	}
	else
	{
		buffSpeedTimer = 0.0;
		buffSpeed = 0.0;
	}
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
	if (amt < 0.0)
	{
		amt = amt * -1.0f; //Set amount to positive
	}
	if (amt > buffAtk)
	{
		//Will only apply buff if it is stronger than the current buff.
		buffAtk = amt;
		buffAtkTimer = time;
	}
}

void Character::debuffAttack(float amt, float time)
{
	if (amt > 0.0)
	{
		amt = amt * -1.0f; //Set amount to negative
	}
	if (amt < debuffAtk)
	{
		//Will only apply debuff if it reduces the stat even more than the current debuff.
		debuffAtk = amt;
		debuffAtkTimer = time;
	}
}

void Character::buffDefense(float amt, float time)
{
	if (amt < 0.0)
	{
		amt = amt * -1.0f; //Set amount to positive
	}
	if (amt > debuffDef)
	{
		buffDef = amt;
		buffDefTimer = time;
	}
}

void Character::debuffDefense(float amt, float time)
{
	if (amt > 0.0)
	{
		amt = amt * -1.0f;
	}
	if (amt < debuffDef)
	{
		debuffDef = amt;
		debuffDefTimer = time;
	}
}

void Character::buffMoveSpeed(float amt, float time)
{
	if (amt < 0.0)
	{
		amt = amt * -1.0f;
	}
	if (amt > buffSpeed)
	{
		buffSpeed = amt;
		buffSpeedTimer = time;
	}
}

void Character::debuffMoveSpeed(float amt, float time)
{
	if (amt > 0.0)
	{
		amt = amt * -1.0f;
	}
	if (amt < debuffSpeed)
	{
		debuffSpeed = amt;
		debuffSpeedTimer = time;
	}
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
