#include "DataManager.h"
/*
* Will save a player objects stats in a certain order
* per line.
* When loading the player.game file in the data folder,
* you must read it in the same order as it was saved.
*/
void DataManager::SavePlayerData(Player& player)
{
	fstream playerFile;
	// Save player stats to a PlayerData.game
	playerFile.open("data/player.game", ios::out);
	if (playerFile.is_open())
	{
		//Health/Mana/Souls
		playerFile << player.getMaxHealth() << endl;
		playerFile << player.getMaxMana() << endl;
		playerFile << player.getMonsterSouls() << endl;

		//Base Stats
		playerFile << player.getBaseAttack() << endl;
		playerFile << player.getBaseDefense() << endl;
		playerFile << player.getBaseMoveSpeed() << endl;

		//Element Levels
		playerFile << player.getFireLevel() << endl;
		playerFile << player.getWaterLevel() << endl;
		playerFile << player.getEarthLevel() << endl;
		playerFile << player.getAirLevel() << endl;
		playerFile << player.getElectricityLevel() << endl;
		playerFile << player.getIceLevel() << endl;
		playerFile << player.getGravityLevel() << endl;

		playerFile.close();
	}
}

void DataManager::LoadPlayerData(Player& player)
{
	fstream playerFile;
	// Load player data from PlayerData.game
	playerFile.open("data/player.game", ios::in);
	if (playerFile.is_open())
	{
		string line;

		//Health/Mana/Souls
		getline(playerFile, line);
		player.setMaxHealth(stof(line));
		getline(playerFile, line);
		player.setMaxMana(stof(line));
		getline(playerFile, line);
		player.setMonsterSouls(stoi(line));

		//Base Stats
		getline(playerFile, line);
		player.setBaseAttack(stof(line));
		getline(playerFile, line);
		player.setBaseDefense(stof(line));
		getline(playerFile, line);
		player.setBaseMoveSpeed(stof(line));

		//Element Levels
		getline(playerFile, line);
		player.setFireLevel(stoi(line));
		getline(playerFile, line);
		player.setWaterLevel(stoi(line));
		getline(playerFile, line);
		player.setEarthLevel(stoi(line));
		getline(playerFile, line);
		player.setAirLevel(stoi(line));
		getline(playerFile, line);
		player.setElectricityLevel(stoi(line));
		getline(playerFile, line);
		player.setIceLevel(stoi(line));
		getline(playerFile, line);
		player.setGravityLevel(stoi(line));

		playerFile.close();
	}
}
