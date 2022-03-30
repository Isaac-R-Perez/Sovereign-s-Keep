#include "DataManager.h"

void DataManager::SavePlayerData(Player player)
{
	// Save player stats to a PlayerData.game
	playerFile.open("PlayerData.game", ios::out);
	if (playerFile.is_open())
	{
		playerFile << player.getMaxHealth() << endl;
		playerFile << player.getBaseAttack() << endl;

		playerFile.close();
	}
}

void DataManager::LoadPlayerData(Player& player)
{
	// Load player data from PlayerData.game
	playerFile.open("PlayerData.game", ios::in);
	if (playerFile.is_open())
	{
		string line;

		getline(playerFile, line);
		player.setMaxHealth(stof(line));

		getline(playerFile, line);
		player.setBaseAttack(stof(line));

		playerFile.close();
	}
}
