#include "Player.h"

void Player::setSouls(int amt)
{
	monsterSouls = amt;
}

void Player::addSouls(int amt)
{
	monsterSouls += amt;
	if (monsterSouls > maxMonsterSouls)
	{
		monsterSouls = maxMonsterSouls;
	}
}

void Player::spendSouls(int amt)
{
	monsterSouls -= amt;
	if (monsterSouls < 0)
	{
		monsterSouls = 0;
	}
}

int Player::getSouls()
{
	return monsterSouls;
}

void Player::setMaxMana(int amt)
{
	maxMana = amt;
}

int Player::getMaxMana()
{
	return maxMana;
}

void Player::setCurrentMana(int amt)
{
	currentMana = amt;
}

int Player::getCurrentMana()
{
	return currentMana;
}

bool Player::spendMana(int amt)
{
	if (amt < currentMana)
	{
		//Returns true if the player can cast the spell
		currentMana -= amt;
		return true;
	}
	else
	{
		//Returns false if the player can not cast the spell
		return false;
	}
}
