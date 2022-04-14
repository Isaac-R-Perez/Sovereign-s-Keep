#include "Spell.h"
#include <cstdio>

Spell::Spell(Game* g, int rOrder, int defaultSpriteSheet, SpellID id) 
	:Renderable(g, rOrder, defaultSpriteSheet) 
{
	
	
	//this determines which spell was created/cast
	ID = id;

	spellCounter++;
	identifier = spellCounter;
	//add each string name and all info needed for each spell, ALL OF EM
	switch (ID) {
		case SpellID::None: {
			spellName = "NO SPELL";
			manaCost = 0.0f;
			castTime = 0.0f;
			break;
		}

		//single element spells
		case SpellID::Fire: {
			spellName = "Fired Up";
			manaCost = 5.0f;
			castTime = 0.25f;
			break;
		}
		case SpellID::Water: {
			spellName = "Replenish";
			manaCost = 5.0f;
			castTime = 0.25f;
			break;
		}
		case SpellID::Earth: {
			spellName = "Stone Armor";
			manaCost = 5.0f;
			castTime = 0.25f;
			break;
		}
		case SpellID::Air: {
			spellName = "Swift Speed I";
			manaCost = 5.0f;
			castTime = 0.25f;
			break;
		}


		//double element spells
		case SpellID::FireFire: {
			spellName = "Flame Ring";
			manaCost = 15.0f;
			castTime = 1.0f;
			break;
		}
		case SpellID::FireWater: {
			spellName = "Steam Blast";
			manaCost = 10.0f;
			castTime = 0.4f;
			break;
		}
		case SpellID::FireEarth: {
			spellName = "Fireball";
			manaCost = 20.0f;
			castTime = 1.0f;
			break;
		}
		case SpellID::FireAir: {
			spellName = "Fanned Flames I";
			manaCost = 25.0f;
			castTime = 0.25f;
			break;
		}

		case SpellID::WaterWater: {
			spellName = "Water Blast";
			manaCost = 18.0f;
			castTime = 0.5f;
			break;
		}
		case SpellID::WaterEarth: {
			spellName = "Mud Pit";
			manaCost = 50.0f;
			castTime = 1.5f;
			break;
		}
		case SpellID::WaterAir: {
			spellName = "Bubble Shot";
			manaCost = 5.0f;
			castTime = 0.20f;
			break;
		}

		case SpellID::EarthEarth: {
			spellName = "Boulder Sling";
			manaCost = 7.5f;
			castTime = 0.4f;
			break;
		}
		case SpellID::EarthAir: {
			spellName = "Sand Blast";
			manaCost = 10.0f;
			castTime = 0.33f;
			break;
		}

		case SpellID::AirAir: {
			spellName = "Swift Speed II";
			manaCost = 20.0f;
			castTime = 0.5f;
			break;
		}




		//triple element spells
		case SpellID::FireFireFire: {
			spellName = "Fire Soul";
			manaCost = 50.0f;
			castTime = 1.5f;
			break;
		}
		case SpellID::FireFireWater: {
			spellName = "Barrage";
			manaCost = 60.0f;
			castTime = 1.0f;
			break;
		}
		case SpellID::FireFireEarth: {
			spellName = "Fire Elemental";
			manaCost = 25.0f;
			castTime = 0.8f;
			break;
		}
		case SpellID::FireFireAir: {
			spellName = "Firecracker";
			manaCost = 40.0f;
			castTime = 0.5f;
			break;
		}
		case SpellID::FireWaterWater: {
			spellName = "Soothing Waters";
			manaCost = 20.0f;
			castTime = 0.61f;
			break;
		}
		case SpellID::FireWaterEarth: {
			spellName = "Geyser";
			manaCost = 35.0f;
			castTime = 0.75f;
			break;
		}
		case SpellID::FireWaterAir: {
			spellName = "Flash Freeze";
			manaCost = 15.0f;
			castTime = 0.6f;
			break;
		}
		case SpellID::FireEarthEarth: {
			spellName = "Meteor Barrage";
			manaCost = 80.0f;
			castTime = 1.25f;
			break;
		}
		case SpellID::FireEarthAir: {
			spellName = "Fiery Earth Mine";
			manaCost = 15.0f;
			castTime = 0.4f;
			break;
		}
		case SpellID::FireAirAir: {
			spellName = "Fire Storm";
			manaCost = 75.0f;
			castTime = 1.0f;
			break;
		}
		case SpellID::WaterWaterWater: {
			spellName = "Tsunami";
			manaCost = 90.0f;
			castTime = 2.0f;
			break;
		}
		case SpellID::WaterWaterEarth: {
			spellName = "Water Elemental";
			manaCost = 25.0f;
			castTime = 0.8f;
			break;
		}
		case SpellID::WaterWaterAir: {
			spellName = "Waterspout";
			manaCost = 60.0f;
			castTime = 0.95f;
			break;
		}
		case SpellID::WaterEarthEarth: {
			spellName = "Earth Wave";
			manaCost = 45.0f;
			castTime = 0.75f;
			break;
		}
		case SpellID::WaterEarthAir: {
			spellName = "Water Beam";
			manaCost = 40.0f;
			castTime = 0.75f;
			break;
		}
		case SpellID::WaterAirAir: {
			spellName = "Multishot";
			manaCost = 60.0f;
			castTime = 0.5f;
			break;
		}
		case SpellID::EarthEarthEarth: {
			spellName = "Fissure";
			manaCost = 55.0f;
			castTime = 0.75f;
			break;
		}
		case SpellID::EarthEarthAir: {
			spellName = "Saturn's Storm";
			manaCost = 60.0f;
			castTime = 1.0f;
			break;
		}
		case SpellID::EarthAirAir: {
			spellName = "Air Elemental";
			manaCost = 25.0f;
			castTime = 0.8f;
			break;
		}
		case SpellID::AirAirAir: {
			spellName = "Swift Speed III";
			manaCost = 50.0f;
			castTime = 0.5f;
			break;
		}


/*
	These spell IDs are for spells spawned by the main spells
*/
		case SpellID::Meteor: {

			break;
		}
		case SpellID::Explosion1: {

			break;
		}
		case SpellID::WaterBolt: {

			break;
		}
		case SpellID::SustainedExplosion: {

			break;
		}
		case SpellID::ElementalFireball: {

			break;
		}
		case SpellID::ElementalWaterball: {

			break;
		}
		case SpellID::ElementalAirBall: {

			break;
		}
		case SpellID::WaterBallExplosion: {

			break;
		}
		case SpellID::FirePillar: {

			break;
		}
		case SpellID::SmallEarthSpike: {

			break;
		}
		case SpellID::BigEarthSpike: {

			break;
		}
		case SpellID::SaturnRock: {

			break;
		}



		default: {
			spellName = "NO SPELL";
			manaCost = 1000.0f;
			castTime = 10.0f;
			break;
		}
	}

}

/*
	Some spells will apply their effect to the player or enemies then immediatley destroy themeselves (Passives/Buffs),
	while others will have an actual "body" that will render and interact with the world
*/
void Spell::update(double dt) {
	fflush(stdout);
	printf("Casted %s \n", spellName.c_str());
	
	
	switch (ID) {
		

		case SpellID::Fire: {
			
			//apply fire buff, the buff should cancel any other single element buff

			kill();
			break;
		}
		case SpellID::Water: {
			//apply water buff, the buff should cancel any other single element buff

			kill();
			break;
		}
		case SpellID::Earth: {
			//apply earth buff, the buff should cancel any other single element buff

			kill();
			break;
		}
		case SpellID::Air: {
			//apply Air buff, the buff should cancel any other single element buff

			kill();
			break;
		}


						 //double element spells
		case SpellID::FireFire: {
			
			/*
			create a ring of fire on first update

			on every other update, check if not expired
			if not expired, then follow player and check for collision with enemies
			if that enemy DOES NOT have the debuff for this spell, apply effect and apply debuff


			if expired, kill this spell
			
			*/

			//remove later
			kill();
			break;
		}
		case SpellID::FireWater: {
			/*
			on first update move this spell to be in front of the player

			on every other update, check if not expired
			if not expired, then update the animation frames and timers, check if the collision frame is active
			
			if collision frame is active, check if enemy DOES NOT have the debuff for this spell, apply effect and apply debuff


			if animation is done and animationTimer is 0, kill this spell

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::FireEarth: {
			/*
			on first update move this spell to be at player's origin

			on every other update, MOVE THE SPELL IN GIVEN DIRECTION, check if not out of bounds
			if not, then update the animation frames and timers, check if the bolt has hit any enemies,
			if it has, kill this spell and then create an EXPLOSION1 spell at that impact location


			*/

			//remove later
			kill();
			break;
		}
		case SpellID::FireAir: {
			/*
			apply the stacking attack speed buff to the player

			*/

			//remove later
			kill();
			break;
		}

		case SpellID::WaterWater: {
			/*
			create 8? water bolts with random angles, in the direction of the player is facing

			these waterbolts have their own SpellID (and update and render functions)
			the bolts are their own Spell, so just create them here and they will handle generating their own directions/collsions/damage

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::WaterEarth: {
			/*
			on first update move this spell to be in front of the player somewhere

			on every other update, check if not expired
			if not expired, the check for collisions with enemies

			if collision then apply the debuff onto enemies if they dont already have it


			if duration time is over, kill this spell

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::WaterAir: {
			/*
			on first update move this spell to be at the player's origin, set direction and speed

			on every other update, MOVE THIS SPELL, check if not out of bounds and if it has collided with an enemy
			if collision, then deal damage/apply wet to the enemy and kill this spell


			*/

			//remove later
			kill();
			break;
		}

		case SpellID::EarthEarth: {
			/*
			on first update move this spell to be at player origin, set direction and speed

			on every other update, MOVE THIS SPELL, check if not out of bounds and if it has collided with an enemy
			if collision, then deal damage to the enemy and kill this spell

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::EarthAir: {
			/*
			on first update move this spell to be in front of player

			on every other update, update the spell's animation/timers

			on collision timer, check collisions and apply debuff if they occur

			at end of animation, kill this spell

			*/

			//remove later
			kill();
			break;
		}

		case SpellID::AirAir: {
			/*
			apply the stacking swift speed II buff, kill this spell

			*/

			//remove later
			kill();
			break;
		}




							//triple element spells
		case SpellID::FireFireFire: {
			/*
			add the directional attack buff to the player, this buff doesn't stack, but it gets refreshed

			kill spell
			*/

			//remove later
			kill();
			break;
		}
		case SpellID::FireFireWater: {
			/*
			on first update move this spell to be somwhere in front of player, also copy logic of player attack animation loop

			on every other update, check if duration expired, loop animation, then check if spell has collided with enemies
			if collision, check if enemy has this debuff, if not apply this debuff and deal damage

			destroy when expired

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::FireFireEarth: {
			/*
			on first update move this spell to be at player origin,

			on every other update, have the elemental move slowly in the direction of the player
			when moving, play the moving animation

			check if elemental can attack, if so, play attack animation and spawn the correct spell on the apex frame,
			return to walking when done and reset attack timer/timers



			*/

			//remove later
			kill();
			break;
		}
		case SpellID::FireFireAir: {
			/*
			on first update do nothing, 

			on every other update decrement timer, for every 5th of the timer (split timer into 5 parts),
			create an explosion1 at the correct spot in an arc in the direction of the player

			destroy when expired

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::FireWaterWater: {
			/*
			Add a stackable heal buff to the player

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::FireWaterEarth: {
			/*
			on first update move this spell to be somewhere in front of the player

			on every other update, update animation, then check if spell has collided with enemies on collision frame
			if collision and no debuff on enemy, deal damage to that enemy and apply debuff to enemy

			destroy when animation ends

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::FireWaterAir: {
			/*
			on first update move this spell to be at player's origin with correct direction

			on every other update, move the spell in the direction, update animation, then check if spell has collided with enemies
			if collision, deal damage to that enemy and freeze the enemy

			destroy on collision or out of bounds

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::FireEarthEarth: {
			/*
			on first update, set timer to handle spawning meteor cooldown 

			on every other update, check if meteor cooldown in 0,
			if it is, create a meteor  in a random spot around the player

			destroy when duration timer expires

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::FireEarthAir: {
			/*
			on first update , move this spell in front of the player

			on every other update, check if the mine has collided with an enemy,
			if it has kill the mine and create an explosion at that point

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::FireAirAir: {
			/*
			on first update, set timer to handle spawning fire column cooldown

			on every other update, check if column cooldown in 0,
			if it is, create a column  in a random spot around the player, reset timer

			destroy when duration timer expires

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::WaterWaterWater: {
			/*
			on first update move this spell far away in the direction of the player

			on every other update, update the animation of the spell,
			on collision frame, deal TONS of damage to enemies hit

			destroy when animation ends

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::WaterWaterEarth: {
			/*
			on first update move this spell to be at player origin,

			on every other update, have the elemental move slowly in the direction of the player
			when moving, play the moving animation

			check if elemental can attack, if so, play attack animation and spawn the correct spell on the apex frame,
			return to walking when done and reset attack timer/timers



			*/

			//remove later
			kill();
			break;
		}
		case SpellID::WaterWaterAir: {
			/*
			on first update move this spell to be at player's origin with correct direction, COPY CODE TO LOOP THE ANIMATION

			on every other update, move the spell in the direction, update animation, then check if spell has collided with enemies
			if collision, deal damage to that enemy 

			destroy when duration runs out

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::WaterEarthEarth: {
			/*
			on first update move this spell to be at player's origin with correct direction, set spawn spike timer

			on every other update, move the spell in the direction, check if timer is 0
			if timer is 0, reset it and create a SMALL earth spike at that location

			destroy when duration ends

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::WaterEarthAir: {
			/*
			on first update move this spell far away in the direction of the player

			on every other update, update the animation of the spell,
			on collision frame, deal damage to enemies hit

			destroy when animation ends

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::WaterAirAir: {
			/*
			Add the multishot buff to the player, kill this spell

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::EarthEarthEarth: {
			/*
			create 4 Large Earth Spikes in the four cardinal direction around the player

			destroy this spell

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::EarthEarthAir: {
			/*
			
				create 8 Saturn rocks

				(these rocks will given themeselves a random distance/angle/rotation speed and will follow the player)

				destroy this spell

			*/

			//remove later
			kill();
			break;
		}
		case SpellID::EarthAirAir: {
			/*
			on first update move this spell to be at player origin,

			on every other update, have the elemental move slowly in the direction of the player
			when moving, play the moving animation

			check if elemental can attack, if so, play attack animation and spawn the correct spell on the apex frame,
			return to walking when done and reset attack timer/timers



			*/

			//remove later
			kill();
			break;
		}
		case SpellID::AirAirAir: {
			/*
			apply the stacking Swift Speed III buff to the palyer

			destroy this spell

			*/

			//remove later
			kill();
			break;
		}










		 /*
		These are the update functions for the spells spawned by the main spells
		*/
		case SpellID::Meteor: {

			break;
		}
		case SpellID::Explosion1: {

			break;
		}
		case SpellID::WaterBolt: {

			break;
		}
		case SpellID::SustainedExplosion: {

			break;
		}
		case SpellID::ElementalFireball: {

			break;
		}
		case SpellID::ElementalWaterball: {

			break;
		}
		case SpellID::ElementalAirBall: {

			break;
		}
		case SpellID::WaterBallExplosion: {

			break;
		}
		case SpellID::FirePillar: {

			break;
		}
		case SpellID::SmallEarthSpike: {

			break;
		}
		case SpellID::BigEarthSpike: {

			break;
		}
		case SpellID::SaturnRock: {

			break;
		}




	}
}


void Spell::render() {

}


