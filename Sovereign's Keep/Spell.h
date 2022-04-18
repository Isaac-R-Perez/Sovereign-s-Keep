#pragma once
#include "Renderable.h"

/*
	This class will handle the spell combinations, and will also hold all of the logic pertaining to 
	the spells that the player can cast. Some spells will be rendered as objects, while some will have no rendering, such as passive buffs.
*/

//static uint32_t spellCounter = 0;


/// <summary>
///						SPELL DAMAGE BYPASSES DEFENSES!
/// </summary>

const float FLAME_RING_ANIMATION_TIMER = 0.15f;
const float FLAME_RING_WIDTH = 0.275f;
const float FLAME_RING_HEIGHT = 0.325f;
const float FLAME_RING_DAMAGE_MULT = 0.75f;

const float FIREBALL_ANIMATION_TIMER = 0.1f;
const float FIREBALL_WIDTH = 0.045f;
const float FIREBALL_HEIGHT = 0.04f;
const float FIREBALL_DAMAGE_MULT = 2.5f; //fireball damage = player_base_damage * 1.25f


const float WATERBOLT_ANIMATION_TIMER = 0.02f;
const int WATERBOLT_AMOUNT = 20;
const float WATERBOLT_WIDTH = 0.075f;
const float WATERBOLT_HEIGHT = 0.06f;
const float WATERBOLT_DAMAGE_MULT = 1.5f;

const float BUBBLE_SHOT_ANIMATION_TIMER = 0.05;
const float BUBBLE_SHOT_WIDTH = 0.1f;
const float BUBBLE_SHOT_HEIGHT = 0.15f;
const float BUBBLE_SHOT_DAMAGE_MULT = 2.5f;


//base width, call resize to alter the explosion size
const float EXPLOSION1_WIDTH = 0.3f;
const float EXPLOSION1_ANIMATION_TIMER = 0.021f;
const float EXPLOSION1_DAMAGE_MULT = 3.5f; //all explosion1s deal the same damage

const float STEAM_BLAST_WIDTH = 0.3f;
const float STEAM_BLAST_ANIMATION_TIMER = 0.021f;
const float STEAM_BLAST_DAMAGE_MULT = 1.75f; //all explosion1s deal the same damage

const float MUD_WIDTH = 0.21f;
const float MUD_HEIGHT = 0.325f;

const float BOULDER_ANIMATION_TIMER = 0.02f;
const float BOULDER_WIDTH = 0.15f;
const float BOULDER_HEIGHT = 0.175f;
const float BOULDER_DAMAGE_MULT = 3.0f;


const float AIR_SPIKE_ANIMATION_TIMER = 0.02f;
const float AIR_SPIKE_WIDTH = 0.05f;
const float AIR_SPIKE_HEIGHT = 0.15f;
const float AIR_SPIKE_DAMAGE_MULT = 1.75f;


const float GEYSER_ANIMATION_TIMER = 0.05f;
const float GEYSER_WIDTH = 0.08f;
const float GEYSER_HEIGHT = 0.225f;
const float GEYSER_DAMAGE_MULT = 5.0f;

const float FFREEZE_ANIMATION_TIMER = 0.025;
const float FFREEZE_WIDTH = 0.25f;
const float FFREEZE_HEIGHT = 0.4f;
const float FFREEZE_DAMAGE_MULT = 2.0f;

const float BARRAGE_ANIMATION_TIMER = 0.0175f;
const float BARRAGE_WIDTH = 0.2f;
const float BARRAGE_HEIGHT = 0.275f;
const float BARRAGE_DAMAGE_MULT = 1.1f;

const float GOLEM_WALKING_ANIMATION_TIMER = 0.06f;
const float GOLEM_FIRE_ATTACK_TIMER = 0.08f;
const float GOLEM_WATER_ATTACK_TIMER = 0.1f;
const float GOLEM_AIR_ATTACK_TIMER = 0.15f;

const float GOLEM_WALKING_WIDTH = 0.05f;
const float GOLEM_WALKING_HEIGHT = 0.075f;
const float GOLEM_ATTACKING_WIDTH = 0.061f;
const float GOLEM_ATTACKING_HEIGHT = 0.092f;

const float GOLEM_ATTACK_TIMER = 1.0f;
const float FIRE_GOLEM_DAMAGE_MULT = 2.5f;
const float WATER_GOLEM_SIZE_MULT = 0.8f;
const float AIR_GOLEM_SIZE_MULT = 1.21f;

const int FIRECRACKER_AMOUNT = 7;
const float FIRECRACKER_TIMER = 0.135f;


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

	Meteor, //for the meteor barrage spell
	
	Explosion1,//for fireball explosion, meteor impact
	
	WaterBolt, //for the Water Blast spell
	
	SustainedExplosion,//for the Barrage spell
	
	ElementalFireball,//attack for fire elemental
	
	ElementalWaterball,//attack for water elemental
	
	ElementalAirBall, //attack for air elemental
	
	WaterBallExplosion,//explosion of the Exploding WaterBall spell
	
	FirePillar, //spawned by the FireStorm spell

	SmallEarthSpike, //created by Earth Wave

	BigEarthSpike, //created by Fissure

	SaturnRock, //rock created by Saturn's storm

	knockback, //used for when an enemy is hit by a basic attack(/spell?)

};


// This enum determines how much explosion damage to apply
enum class ExplosionType {
	Fireball, Meteor, Firecracker, FieryEarthMine,
};

class Spell : public Renderable {
public:

	Spell(Game* g, int rOrder, int defaultSpriteSheet, SpellID id);


	void render();
	void update(double dt);

	float getManaCost() { return manaCost; }
	float getCastTime() { return castTime; }

	//uint32_t getIdentifier() { return identifier; }

	void setExplosionType(ExplosionType t) { eType = t; }

	//keeps code cleaner
	void renderThisSpell(float stride);

	void setDirection(glm::vec3 dir) { direction = dir; }


private:

	float manaCost;
	float castTime;

	//used for RENDERING IN GUI ONLY, use the ENUM to identify this spell
	std::string spellName;

	//use this to identify which spell this is
	SpellID ID;

	//uint32_t identifier;


	//when this timer reaches 0, the spell is over
	float duration;

	//if 0, the spell can deal damage
	float damageTimer;


	//is this spell newly created?
	bool firstUpdate;

	//holds the timer for the animation frames switching
	float animationTimer;

	//holds the number of frames of animation - 1
	int animationFrames;

	//holds the current animation frame of this spell
	int currentAnimationFrame;

	//use this for spells that travel along a path
	glm::vec3 direction;

	//use this for spells that travel along a path
	float moveSpeed;

	//this is false intially, set this true whenever you set firstUpdate false
	bool startLoop;

	//determines how much explosion damage this spell does
	ExplosionType eType;

	//true if the spell should flip travel direction
	bool flipped;


	//for golems
	float attackTimer;

	//is true on the frame that the spell can deal damage on this frame
	bool collisionFrame;

	//true if damage on the collision frame has been dealt
	bool dealtDamage;


	//spawnDistribution(numberEngine)
	std::uniform_real_distribution<float> floatDistribution;


	//holds the ID of the enemy that is closest to player
	uint32_t nearestEnemyID;

	bool WALKING;
	bool ATTACKING;
	bool FIND_ENEMY;

	Renderable* closestEnemy;

	



};