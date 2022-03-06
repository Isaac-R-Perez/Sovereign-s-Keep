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

void Player::removeSouls(int amt)
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
