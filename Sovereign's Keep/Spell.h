#pragma once
#include "Renderable.h"

/*
	This class will handle the spell combinations, and will also hold all of the logic pertaining to 
	the spells that the player can cast. Some spells will be rendered as objects, while some will have no rendering, such as passive buffs.
*/

static uint32_t spellCounter = 0;

enum class SpellID {
	
	//NO (NEW) SPELL CREATED
	None,

	//single element spells
	Fire, Water, Earth, Air, Elec, Ice, Grav,

	//double element spells
	FireFire, FireWater, FireEarth, FireAir, FireElec, FireIce, FireGrav,
	WaterWater, WaterEarth, WaterAir, WaterElec, WaterIce, WaterGrav,
	EarthEarth, EarthAir, EarthElec, EarthIce, EarthGrav,
	AirAir, AirElec, AirIce, AirGrav,
	ElecElec, ElecIce, ElecGrav,
	IceIce, IceGrav,
	GravGrav,

	//triple element spells FIRE FIRST
	FireFireFire, FireFireWater, FireFireEarth, FireFireAir, FireFireElec, FireFireIce, FireFireGrav,
	FireWaterWater, FireWaterEarth, FireWaterAir, FireWaterElec, FireWaterIce, FireWaterGrav,
	FireEarthEarth, FireEarthAir, FireEarthElec, FireEarthIce, FireEarthGrav,
	FireAirAir, FireAirElec, FireAirIce, FireAirGrav,
	FireElecElec, FireElecIce, FireElecGrav,
	FireIceIce, FireIceGrav,
	FireGravGrav,

	//triple WATER FIRST
	WaterWaterWater, WaterWaterEarth, WaterWaterAir, WaterWaterElec, WaterWaterIce, WaterWaterGrav,
	WaterEarthEarth, WaterEarthAir, WaterEarthElec, WaterEarthIce, WaterEarthGrav,
	WaterAirAir, WaterAirElec, WaterAirIce, WaterAirGrav,
	WaterElecElec, WaterElecIce, WaterElecGrav,
	WaterIceIce, WaterIceGrav,
	WaterGravGrav,
	
	//triple EARTH FIRST
	EarthEarthEarth, EarthEarthAir, EarthEarthElec, EarthEarthIce, EarthEarthGrav,
	EarthAirAir, EarthAirElec, EarthAirIce, EarthAirGrav,
	EarthElecElec, EarthElecIce, EarthElecGrav,
	EarthIceIce, EarthIceGrav,
	EarthGravGrav,

	//triple AIR FIRST
	AirAirAir, AirAirElec, AirAirIce, AirAirGrav,
	AirElecElec, AirElecIce, AirElecGrav,
	AirIceIce, AirIceGrav,
	AirGravGrav,

	//triple ELEC first
	ElecElecElec, ElecElecIce, ElecElecGrav,
	ElecIceIce, ElecIceGrav,
	ElecGravGrav,

	//triple ICE
	IceIceIce, IceIceGrav,
	IceGravGrav,

	//tiple gravity
	GravGravGrav,


};

class Spell : public Renderable {
public:

	Spell(Game* g, int rOrder, int defaultSpriteSheet, SpellID id);


	void render();
	void update(double dt);

	float getManaCost() { return manaCost; }
	float getCastTime() { return castTime; }

	uint32_t getIdentifier() { return identifier; }


private:

	float manaCost;
	float castTime;

	//used for RENDERING IN GUI ONLY, use the ENUM to identify this spell
	std::string spellName;

	//use this to identify which spell this is
	SpellID ID;

	uint32_t identifier;


};