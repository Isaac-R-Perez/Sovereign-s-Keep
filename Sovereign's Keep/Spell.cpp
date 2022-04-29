#include "Spell.h"
#include "Player.h"
#include "Enemy.h"
#include "Basic_Attack.h"
#include <cstdio>
#include "GLM/gtx/vector_angle.hpp"
#include "GLM/gtx/transform.hpp"

//const float FLIP_TIME = 0.25f;

Spell::Spell(Game* g, int rOrder, int defaultSpriteSheet, SpellID id) 
	:Renderable(g, rOrder, defaultSpriteSheet) 
{
	
	
	//this determines which spell was created/cast
	ID = id;

	//spellCounter++;
	//identifier = spellCounter;
	currentAnimationFrame = 0;
	firstUpdate = true;
	animationTimer = 0.0f;
	flipped = false;
	collisionFrame = false;
	damageTimer = 0.0f;
	dealtDamage = false;
	nearestEnemyID = 0;
	ATTACKING = false;
	WALKING = false;
	FIND_ENEMY = false;
	closestEnemy = nullptr;
	attackTimer = 0.0f;
	
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
			castTime = 0.2f;
			duration = 1200.0f;
			break;
		}
		case SpellID::Water: {
			spellName = "Replenish";
			manaCost = 5.0f;
			castTime = 0.2f;
			duration = 1200.0f;
			break;
		}
		case SpellID::Earth: {
			spellName = "Stone Armor";
			manaCost = 5.0f;
			castTime = 0.2f;
			duration = 1200.0f;
			break;
		}
		case SpellID::Air: {
			spellName = "Swift Speed I";
			manaCost = 5.0f;
			castTime = 0.2f;
			duration = 1200.0f;
			break;
		}


		//double element spells
		case SpellID::FireFire: {
			spellName = "Flame Ring";
			manaCost = 50.0f;
			castTime = 0.75f;
			duration = 10.0f;
			animationFrames = 2;
			setTexture(static_cast<int>(SPRITE_SHEETS::flame_ring));
			resize(FLAME_RING_WIDTH, FLAME_RING_HEIGHT);
			break;
		}
		case SpellID::FireWater: {
			spellName = "Steam Blast";
			manaCost = 35.0f;
			castTime = 0.2f;
			animationFrames = 7;
			setTexture(static_cast<int>(SPRITE_SHEETS::steam_blast));
			resize(STEAM_BLAST_WIDTH, STEAM_BLAST_WIDTH);
			break;
		}
		case SpellID::FireEarth: {
			spellName = "Fireball";
			manaCost = 20.0f;
			castTime = 0.15f;
			duration = 1.45f; //lifetime of firebolt
			animationFrames = 3; //firebolt
			setTexture(static_cast<int>(SPRITE_SHEETS::fireball));
			moveSpeed = 0.85f;
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			resize(FIREBALL_WIDTH, FIREBALL_HEIGHT);
			break;
		}
		case SpellID::FireAir: {
			spellName = "Fanned Flames I";
			manaCost = 50.0f;
			castTime = 0.25f;
			duration = 17.0f;
			break;
		}

		case SpellID::WaterWater: {
			spellName = "Water Blast";
			manaCost = 18.0f;
			castTime = 0.5f;
			// from 
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			floatDistribution = std::uniform_real_distribution<float>(0.0, 2.0f * glm::pi<float>());
			break;
		}
		case SpellID::WaterEarth: {
			spellName = "Mud Pit";
			manaCost = 50.0f;
			castTime = 0.65f;
			duration = 20.0f;
			setTexture(static_cast<int>(SPRITE_SHEETS::mud_pit));
			resize(MUD_WIDTH, MUD_HEIGHT);
			
			break;
		}
		case SpellID::WaterAir: {
			spellName = "Bubble Shot";
			manaCost = 5.0f;
			castTime = 0.05f;
			duration = 1.6f; //lifetime of firebolt
			animationFrames = 8; //firebolt
			setTexture(static_cast<int>(SPRITE_SHEETS::bubble_shot));
			moveSpeed = 0.65f;
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			resize(BUBBLE_SHOT_WIDTH, BUBBLE_SHOT_HEIGHT);
			break;
		}

		case SpellID::EarthEarth: {
			spellName = "Boulder Sling";
			manaCost = 45.0f;
			castTime = 0.56f;
			duration = 1.45f; //lifetime of firebolt
			animationFrames = 2; //firebolt
			setTexture(static_cast<int>(SPRITE_SHEETS::boulder_shot));
			moveSpeed = 0.55f;
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			resize(BOULDER_WIDTH, BOULDER_HEIGHT);
			break;
		}
		case SpellID::EarthAir: {
			spellName = "Air Spike";
			manaCost = 8.0f;
			castTime = 0.12f;
			animationFrames = 10; //firebolt
			setTexture(static_cast<int>(SPRITE_SHEETS::air_spike));
			resize(AIR_SPIKE_WIDTH, AIR_SPIKE_HEIGHT);
			break;
		}

		case SpellID::AirAir: {
			spellName = "Swift Speed II";
			manaCost = 25.0f;
			castTime = 0.5f;
			duration = 10.0f;
			direction = glm::vec3(1.0f, 0.0f, 0.0f);

			break;
		}




		//triple element spells
		case SpellID::FireFireFire: {
			spellName = "Fire Soul";
			manaCost = 50.0f;
			castTime = 1.5f;
			duration = 15.0f;
			break;
		}
		case SpellID::FireFireWater: {
			spellName = "Barrage";
			manaCost = 60.0f;
			castTime = 1.0f;
			duration = 4.5f; 
			animationFrames = 7;
			setTexture(static_cast<int>(SPRITE_SHEETS::barrage));
			resize(BARRAGE_WIDTH, BARRAGE_HEIGHT);
			break;
		}
		case SpellID::FireFireEarth: {
			spellName = "Fire Elemental";
			manaCost = 25.0f;
			castTime = 0.8f;
			duration = 45.0f; //golem lasts this long
			moveSpeed = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentMoveSpeed();
			//set animation frames in update
			//set texture in render
			//resize(GOLEM_WIDTH, GOLEM_HEIGHT);
			WALKING = true;
			ATTACKING = false;
			FIND_ENEMY = true;
			//flipTimer = FLIP_TIME;
			break;
		}
		case SpellID::FireFireAir: {
			spellName = "Firecracker";
			manaCost = 40.0f;
			castTime = 0.5f;
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			animationFrames = 0;
			break;
		}
		case SpellID::FireWaterWater: {
			spellName = "Soothing Waters";
			manaCost = 20.0f;
			castTime = 0.61f;
			duration = 15.0f;
			break;
		}
		case SpellID::FireWaterEarth: {
			spellName = "Geyser";
			manaCost = 35.0f;
			castTime = 0.4f;
			animationFrames = 14; //firebolt
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			moveSpeed = 0.05f;
			setTexture(static_cast<int>(SPRITE_SHEETS::geyser));
			resize(GEYSER_HEIGHT, GEYSER_HEIGHT);
			break;
		}
		case SpellID::FireWaterAir: {
			spellName = "Flash Freeze";
			manaCost = 15.0f;
			castTime = 0.45f;
			animationFrames = 14; //firebolt
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			moveSpeed = 0.075f;
			setTexture(static_cast<int>(SPRITE_SHEETS::flash_freeze));
			resize(FFREEZE_WIDTH, FFREEZE_HEIGHT);
			break;
		}
		case SpellID::FireEarthEarth: {
			spellName = "Meteor Barrage";
			manaCost = 80.0f;
			castTime = 1.25f;
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			animationFrames = 0;
			floatDistribution = std::uniform_real_distribution<float>(0.0, 2.0f * glm::pi<float>());
			duration = 5.0f;
			break;
		}
		case SpellID::FireEarthAir: {
			spellName = "Fiery Earth Mine";
			manaCost = 7.0f;
			castTime = 0.2f;
			duration = EARTH_MINE_DURATION; //lifetime of firebolt
			animationFrames = 9; //firebolt
			setTexture(static_cast<int>(SPRITE_SHEETS::earth_mine));
			moveSpeed = 0.275f;
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			resize(EARTH_MINE_WIDTH, EARTH_MINE_HEIGHT);
			break;
		}
		case SpellID::FireAirAir: {
			spellName = "Fire Storm";
			manaCost = 45.0f;
			castTime = 1.0f;
			duration = 7.5f;
			animationFrames = 0;
			floatDistribution = std::uniform_real_distribution<float>(0.0, 2.0f * glm::pi<float>());
			break;
		}
		case SpellID::WaterWaterWater: {
			spellName = "Tsunami";
			manaCost = 90.0f;
			castTime = 2.0f;
			animationFrames = 13;
			setTexture(static_cast<int>(SPRITE_SHEETS::tsunami));
			resize(TSUNAMI_WIDTH, TSUNAMI_HEIGHT);
			break;
		}
		case SpellID::WaterWaterEarth: {
			spellName = "Water Elemental";
			manaCost = 25.0f;
			castTime = 0.8f;
			duration = 45.0f; //golem lasts this long
			moveSpeed = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentMoveSpeed() / 3.0f;
			WALKING = true;
			ATTACKING = false;
			FIND_ENEMY = true;
			attackTimer = GOLEM_WATER_ATTACK_TIMER;
			break;
		}
		case SpellID::WaterWaterAir: {
			spellName = "Waterspout";
			manaCost = 60.0f;
			castTime = 0.95f;
			duration = 4.5f;
			animationFrames = 11;
			moveSpeed = 0.5f;
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			damageTimer = WATER_SPOUT_DAMAGE_TIMER;
			setTexture(static_cast<int>(SPRITE_SHEETS::water_spout));
			resize(WATER_SPOUT_WIDTH, WATER_SPOUT_HEIGHT);
			break;
		}
		case SpellID::WaterEarthEarth: {
			spellName = "Earth Wave";
			manaCost = 45.0f;
			castTime = 0.75f;
			duration = 2.75f;
			moveSpeed = 0.65f;
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			damageTimer = EARTH_WAVE_SPAWN_TIMER;
			break;
		}
		case SpellID::WaterEarthAir: {
			spellName = "Water Beam";
			manaCost = 40.0f;
			castTime = 0.75f;
			animationFrames = 23;
			setTexture(static_cast<int>(SPRITE_SHEETS::water_beam));
			resize(WATER_BEAM_WIDTH, WATER_BEAM_HEIGHT);
			break;
		}
		case SpellID::WaterAirAir: {
			spellName = "Multishot";
			manaCost = 45.0f;
			castTime = 0.5f;
			duration = 20.0f;
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
			duration = 5.0f;
			// from 
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			floatDistribution = std::uniform_real_distribution<float>(0.0, 2.0f * glm::pi<float>());
			damageTimer = 0.0f;
			break;
		}
		case SpellID::EarthAirAir: {
			spellName = "Air Elemental";
			manaCost = 25.0f;
			castTime = 0.8f;
			duration = 45.0f; //golem lasts this long
			moveSpeed = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentMoveSpeed();
			WALKING = true;
			ATTACKING = false;
			FIND_ENEMY = true;
			attackTimer = GOLEM_AIR_ATTACK_TIMER;
			break;
		}
		case SpellID::AirAirAir: {
			spellName = "Swift Speed III";
			manaCost = 50.0f;
			castTime = 0.5f;
			duration = 5.0f;
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			animationFrames = 0;
			damageTimer = WHIRLWIND_SPAWN_TIMER;
			break;
		}


/*
	These spell IDs are for spells spawned by the main spells
*/
		case SpellID::Meteor: {
			animationFrames = 4;
			//setTexture(static_cast<int>(SPRITE_SHEETS::explosion1));
			resize(METEOR_WIDTH, METEOR_HEIGHT);
			duration = METEOR_FLIGHT_TIME;
			moveSpeed = 1.25f;
			break;
		}
		case SpellID::Whirlwind: {
			animationFrames = 10;
			//setTexture(static_cast<int>(SPRITE_SHEETS::explosion1));
			resize(WHIRLWIND_WIDTH, WHIRLWIND_HEIGHT);
			duration = WHIRLWIND_DURATION;
			moveSpeed = 1.0f;
			break;
		}
		case SpellID::Explosion1: {
			spellName = "Explosion1";
			animationFrames = 10; 
			//setTexture(static_cast<int>(SPRITE_SHEETS::explosion1));
			resize(EXPLOSION1_WIDTH, EXPLOSION1_WIDTH);
			break;
		}
		case SpellID::WaterBolt: {
			spellName = "WaterBolt";
			duration = 1.45f; //lifetime of firebolt
			animationFrames = 11; //waterbolt
			//setTexture(static_cast<int>(SPRITE_SHEETS::waterbolt));
			moveSpeed = 0.65f;
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			resize(WATERBOLT_WIDTH, WATERBOLT_HEIGHT);
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
			animationFrames = 9;
			//setTexture(static_cast<int>(SPRITE_SHEETS::explosion1));
			resize(FIRE_BEAM_WIDTH, FIRE_BEAM_HEIGHT);
			break;
		}
		case SpellID::SmallEarthSpike: {
			animationFrames = 4;
			//setTexture(static_cast<int>(SPRITE_SHEETS::earth_spike));
			resize(EARTH_WAVE_WIDTH, EARTH_WAVE_HEIGHT);
			break;
		}
		case SpellID::BigEarthSpike: {
			animationFrames = 15;
			//setTexture(static_cast<int>(SPRITE_SHEETS::explosion1));
			resize(FISSURE_WIDTH, FISSURE_HEIGHT);
			break;
		}
		case SpellID::SaturnRock: {
			//animationFrames = 11;
			castTime = 0.0f; //used for angle
			duration = SATURN_ROCK_AIR_TIME;
			moveSpeed = SATURN_ROCK_BASE_ROTATION_SPEED;
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			damageTimer = 0.1f;
			setTexture(static_cast<int>(SPRITE_SHEETS::saturn_rock));
			resize(SATURN_ROCK_WIDTH, SATURN_ROCK_HEIGHT);
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
	//fflush(stdout);
	//printf("Casted %s \n", spellName.c_str());
	

	std::multimap<int, Renderable*>::iterator itr;
	std::multimap<int, Renderable*> queue = getGame()->getRenderQueue();

	
	switch (ID) {
		

		case SpellID::Fire: {
			
			//apply fire buff, the buff should cancel any other single element buff

			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Fire)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Fire);
			}
			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Water)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Water);
			}
			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Earth)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Earth);
			}
			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Air)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Air);
			}

			dynamic_cast<Player*>(getGame()->getPlayer())->addBuff(spellBuff(duration, ID));

			kill();
			break;
		}
		case SpellID::Water: {
			//apply water buff, the buff should cancel any other single element buff

			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Fire)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Fire);
			}
			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Water)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Water);
			}
			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Earth)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Earth);
			}
			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Air)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Air);
			}

			dynamic_cast<Player*>(getGame()->getPlayer())->addBuff(spellBuff(duration, ID));

			kill();
			break;
		}
		case SpellID::Earth: {
			//apply earth buff, the buff should cancel any other single element buff

			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Fire)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Fire);
			}
			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Water)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Water);
			}
			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Earth)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Earth);
			}
			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Air)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Air);
			}

			dynamic_cast<Player*>(getGame()->getPlayer())->addBuff(spellBuff(duration, ID));


			kill();
			break;
		}
		case SpellID::Air: {
			//apply Air buff, the buff should cancel any other single element buff
			

			//check if any other basic buff is applied, if it is, remove it then apply new buff

			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Fire)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Fire);
			}
			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Water)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Water);
			}
			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Earth)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Earth);
			}
			if (dynamic_cast<Player*>(getGame()->getPlayer())->searchSpellBuff(SpellID::Air)) {
				dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::Air);
			}

			
			dynamic_cast<Player*>(getGame()->getPlayer())->addBuff(spellBuff(duration, ID));
			

			

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

			


			glm::mat4 move;
			float alterSize = 0.85f;

			if (firstUpdate) {
				//do first update things
				firstUpdate = false;
				
				move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin() - getOrigin()));
				updatePosition(move);

				//update hitbox
				//getHitBox().updateHitBox(getOrigin(), getWidth() * alterSize, getWidth()* alterSize, getWidth()* alterSize, getWidth()* alterSize); //explosion size can be set by the creating spell


			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}

				

				move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin() - getOrigin()));
				updatePosition(move);

				getHitBox().updateHitBox(getOrigin(), getWidth()* alterSize, getWidth()* alterSize, getHeight()* alterSize, getHeight()* alterSize); //explosion size can be set by the creating spell

				//play explosion animation, enable collision on a certain frame
				

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = FLAME_RING_ANIMATION_TIMER;
					currentAnimationFrame++;

					//destroy explosion at end of animation
					if (currentAnimationFrame > animationFrames) {
						currentAnimationFrame = 0;
					}
				}





				if (damageTimer <= 0.0f)
				{

					//COLLISION CHECK
					if (!queue.empty())
					{
						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {


								//deal damage
								float damage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * FLAME_RING_DAMAGE_MULT;
								dynamic_cast<Enemy*>(itr->second)->alterHealth(-(damage));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.075f, SpellID::knockback));
								dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(glm::normalize(itr->second->getOrigin() - getOrigin()));

								damageTimer = 0.33f; //can deal damage every 1 second

								//printf("PLAYER IS COLLIDING WITH ENEMY\n");
								//break;




							}
						}



					}

				}


					damageTimer -= dt;



					duration -= dt;
					if (duration <= 0.0f) {
						kill();
					}



			}






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


			glm::mat4 move;


			if (firstUpdate) {
				//do first update things
				firstUpdate = false;

				float sizeAlter = 0.9f;
				float xDistance = 0.0f;

				flipped = dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft();

				if (!flipped) {
					move = glm::translate(glm::mat4(1.0f), glm::vec3(
						dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().x + xDistance, dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().y, 0.0f));

				}
				else
				{
					move = glm::translate(glm::mat4(1.0f), glm::vec3(
						dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().x - xDistance, dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().y, 0.0f));
				}

				
				updatePosition(move);

				//update hitbox
				getHitBox().updateHitBox(getOrigin(), getWidth() * sizeAlter, getWidth() * sizeAlter, getWidth() * sizeAlter, getWidth() * sizeAlter); //explosion size can be set by the creating spell


			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}



				//play explosion animation, enable collision on a certain frame
				if (currentAnimationFrame == 1) {
					collisionFrame = true;
				}
				else
				{
					collisionFrame = false;
				}

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = STEAM_BLAST_ANIMATION_TIMER;
					currentAnimationFrame++;

					//destroy explosion at end of animation
					if (currentAnimationFrame > animationFrames) {
						kill();
					}
				}





				//only check collision on the collisionFrame
				if (collisionFrame && !dealtDamage) {

					//COLLISION CHECK
					if (!queue.empty())
					{

						

							for (itr = queue.begin(); itr != queue.end(); ++itr) {

								//checks collision with ENEMY renderable in the queue
								if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {


									//deal damage
									float explosionDamage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * STEAM_BLAST_DAMAGE_MULT;
									dynamic_cast<Enemy*>(itr->second)->alterHealth(-(explosionDamage));
									dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.885f, SpellID::knockback));
									dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(glm::normalize(itr->second->getOrigin() - getOrigin()));

									//tell the game to not process anymore possible collisions for this spell
									dealtDamage = true;


								}
							}
						




					}
				}








			}





			
			break;
		}
		case SpellID::FireEarth: {
			/*
			on first update move this spell to be at player's origin

			on every other update, MOVE THE SPELL IN GIVEN DIRECTION, check if not out of bounds
			if not, then update the animation frames and timers, check if the bolt has hit any enemies,
			if it has, kill this spell and then create an EXPLOSION1 spell at that impact location


			*/

			glm::mat4 move;


			if (firstUpdate) {
				//do first update things
				move = glm::translate(glm::mat4(1.0f), dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin());

				updatePosition(move);

				//flip the fireball if player is facing left
				if (dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft())
				{
					flip();
					flipped = true;
					direction = glm::vec3(-1.0f, 0.0f, 0.0f);
				}


				firstUpdate = false;
			}
			else
			{
				//initially the fireball cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}




				//play fireball animation
				if (currentAnimationFrame > animationFrames) {
					currentAnimationFrame = 0;
				}

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = FIREBALL_ANIMATION_TIMER;
					currentAnimationFrame++;

					if (currentAnimationFrame > animationFrames) {
						currentAnimationFrame = 0;
					}
				}

				//have the fireball travel
				move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * moveSpeed * dt, 0.0f, 0.0f));
				updatePosition(move);
				

				//update hitbox
				getHitBox().updateHitBox(getOrigin(), FIREBALL_WIDTH, FIREBALL_WIDTH, FIREBALL_HEIGHT, FIREBALL_HEIGHT);


				


				//check collisions here, if collision, destroy this spell and create an explosion spell at that point

			//COLLISION CHECK
				if (!queue.empty())
				{
					Renderable* createdExplosion = nullptr;
					

					for (itr = queue.begin(); itr != queue.end(); ++itr) {

						//checks collision with ENEMY renderable in the queue
						if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {
							


								//deal fireball damage
								float fireballDamage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * FIREBALL_DAMAGE_MULT;
								dynamic_cast<Enemy*>(itr->second)->alterHealth(-(fireballDamage));
								//dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.15f, SpellID::knockback));
								//dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(direction);




								//resize the explosion?
								
								//create an explosion at this fireball's origin
								createdExplosion = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::explosion1), SpellID::Explosion1);
								move = glm::translate(glm::mat4(1.0f), getOrigin());
								createdExplosion->updatePosition(move);

								getGame()->renderableToPendingAdd(createdExplosion);

								//destroy fireball
								kill();


								//printf("PLAYER IS COLLIDING WITH ENEMY\n");
								break;
							
						}

					}


				}




				//lifetime of spell
				duration -= dt;
				if (duration <= 0.0f) {
					kill();
				}

			}






			break;
		}
		case SpellID::FireAir: {
			/*
			apply the stacking attack speed buff to the player

			*/

			dynamic_cast<Player*>(getGame()->getPlayer())->addBuff(spellBuff(duration, ID));

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
			Renderable* createdWaterBolt = nullptr;
			glm::mat4 move;
			glm::mat4 rotation;
		

			//flip the waterBolt direction if player is facing left
			

			for (int i = 0; i < WATERBOLT_AMOUNT; i++) {

				//create water bolt and set its direction + random angle
				createdWaterBolt = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::waterbolt), SpellID::WaterBolt);

				float angle = static_cast<float>(floatDistribution(getGame()->getNumberEngine()));

				rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
				dynamic_cast<Spell*>(createdWaterBolt)->updatePosition(rotation);
				
				dynamic_cast<Spell*>(createdWaterBolt)->setDirection(glm::normalize(rotation * glm::vec4(direction, 0.0f)));


				move = glm::translate(glm::mat4(1.0f), dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin());
				dynamic_cast<Spell*>(createdWaterBolt)->updatePosition(move);

				getGame()->renderableToPendingAdd(createdWaterBolt);



			}

		


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





			glm::mat4 move;
			float xDistance = 0.35f;


			if (firstUpdate) {
				//do first update things
				firstUpdate = false;

				if (dynamic_cast<Player*>(getGame()->getPlayer())->getFacingRight()) {

					move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin() + glm::vec3(xDistance,0.0f,0.0f)));
					updatePosition(move);
				}
				else
				{
					move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin() + glm::vec3(-xDistance, 0.0f, 0.0f)));
					updatePosition(move);
				}


				//update hitbox
				getHitBox().updateHitBox(getOrigin(), getWidth(), getWidth(), getHeight(), getHeight()); //explosion size can be set by the creating spell


			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}



				if (damageTimer <= 0.0f)
				{

					//COLLISION CHECK
					if (!queue.empty())
					{
						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {


								//deal damage
								
								if (!dynamic_cast<Enemy*>(itr->second)->searchSpellBuff(SpellID::WaterEarth)) {
									dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(5.0f, SpellID::WaterEarth));
								}

								

								damageTimer = 0.15f; //can apply effect every 0.15 seconds

								//printf("PLAYER IS COLLIDING WITH ENEMY\n");
								//break;




							}
						}



					}

				}


				damageTimer -= dt;



				duration -= dt;
				if (duration <= 0.0f) {
					kill();
				}



			}







			break;
		}
		case SpellID::WaterAir: {
			/*
			on first update move this spell to be at the player's origin, set direction and speed

			on every other update, MOVE THIS SPELL, check if not out of bounds and if it has collided with an enemy
			if collision, then deal damage/apply wet to the enemy and kill this spell


			*/


			glm::mat4 move;


			if (firstUpdate) {
				//do first update things
				move = glm::translate(glm::mat4(1.0f), dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin());

				updatePosition(move);

				//flip the fireball if player is facing left
				if (dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft())
				{
					flip();
					flipped = true;
					direction = glm::vec3(-1.0f, 0.0f, 0.0f);
				}


				firstUpdate = false;
			}
			else
			{
				//initially the fireball cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}




				//play fireball animation
				if (currentAnimationFrame > animationFrames) {
					currentAnimationFrame = 0;
				}

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = BUBBLE_SHOT_ANIMATION_TIMER;
					currentAnimationFrame++;

					if (currentAnimationFrame > animationFrames) {
						currentAnimationFrame = 0;
					}
				}

				//have the fireball travel
				move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * moveSpeed * dt, 0.0f, 0.0f));
				updatePosition(move);

				float alter = 0.45f;

				//update hitbox
				getHitBox().updateHitBox(getOrigin(), getWidth() * alter, getWidth() * alter, getHeight() * alter, getHeight() * alter);





				//check collisions here, if collision, destroy this spell and create an explosion spell at that point

			//COLLISION CHECK
				if (!queue.empty())
				{
					


					for (itr = queue.begin(); itr != queue.end(); ++itr) {

						//checks collision with ENEMY renderable in the queue
						if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {



							//deal fireball damage
							float damage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * BUBBLE_SHOT_DAMAGE_MULT;
							dynamic_cast<Enemy*>(itr->second)->alterHealth(-(damage));
							dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.75f, SpellID::knockback));
							dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(direction);




							//destroy fireball
							kill();


							//printf("PLAYER IS COLLIDING WITH ENEMY\n");
							

						}

					}


				}




				//lifetime of spell
				duration -= dt;
				if (duration <= 0.0f) {
					kill();
				}

			}



			break;
		}

		case SpellID::EarthEarth: {
			/*
			on first update move this spell to be at player origin, set direction and speed

			on every other update, MOVE THIS SPELL, check if not out of bounds and if it has collided with an enemy
			if collision, then deal damage to the enemy and kill this spell

			*/


			glm::mat4 move;


			if (firstUpdate) {
				//do first update things
				move = glm::translate(glm::mat4(1.0f), dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin());

				updatePosition(move);

				//flip the fireball if player is facing left
				if (dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft())
				{
					flip();
					flipped = true;
					direction = glm::vec3(-1.0f, 0.0f, 0.0f);
				}


				firstUpdate = false;
			}
			else
			{
				//initially the fireball cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}




				//play fireball animation
				if (currentAnimationFrame > animationFrames) {
					currentAnimationFrame = 0;
				}

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = BOULDER_ANIMATION_TIMER;
					currentAnimationFrame++;

					if (currentAnimationFrame > animationFrames) {
						currentAnimationFrame = 0;
					}
				}


				//have the fireball travel
				move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * moveSpeed * dt, 0.0f, 0.0f));
				updatePosition(move);

				float alter = 0.8f;

				//update hitbox
				getHitBox().updateHitBox(getOrigin(), getWidth() * alter, getWidth() * alter, getHeight() * alter, getHeight() * alter);





				//check collisions here, if collision, destroy this spell and create an explosion spell at that point

				if (damageTimer <= 0.0f) {
					dealtDamage = false;
				}

				

			//COLLISION CHECK
				if (!queue.empty())
				{
					
					if (!dealtDamage) {

						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {

								//getHitBox().updateHitBox(getOrigin(), getWidth() * 1.1f, getWidth() * 1.1f, getHeight() * 1.1f, getHeight() * 1.1f);

								//deal fireball damage
								float damage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * BOULDER_DAMAGE_MULT;
								dynamic_cast<Enemy*>(itr->second)->alterHealth(-(damage));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.65f, SpellID::knockback));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(1.5f, SpellID::EarthEarth));
								dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(direction);


								dealtDamage = true;
								damageTimer = 0.45f;

								//destroy fireball
								//kill();


								//printf("PLAYER IS COLLIDING WITH ENEMY\n");


							}

						}
					}



				}



				damageTimer -= dt;

				//lifetime of spell
				duration -= dt;
				if (duration <= 0.0f) {
					kill();
				}

			}



			
			break;
		}
		case SpellID::EarthAir: {
			/*
			on first update move this spell to be in front of player

			on every other update, update the spell's animation/timers

			on collision timer, check collisions and apply debuff if they occur

			at end of animation, kill this spell

			*/



			glm::mat4 move;


			if (firstUpdate) {
				//do first update things
				firstUpdate = false;

				float sizeAlter = 0.95f;
				float smallestDistance = 10000.0f;
				float checkDistance = 0.0f;
				Renderable* nearestEnemy = nullptr;

				//search for nearest enemy here set location of this spell to that enemy's origin

				if (!queue.empty())
				{
					for (itr = queue.begin(); itr != queue.end(); ++itr) {

						if (itr->second->renderOrder == 3) {
							
							if (dynamic_cast<Enemy*>(itr->second)->getAlive())
							{

								checkDistance = glm::length(dynamic_cast<Enemy*>(itr->second)->getOrigin() - dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin());

								if (checkDistance < smallestDistance) {
									smallestDistance = checkDistance;
									nearestEnemy = itr->second;
								}
							}
							
							
						}
						
						

					}

				}


				if (nearestEnemy != nullptr) {
					//move to that enemies origin
					move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Enemy*>(nearestEnemy)->getOrigin()));
					updatePosition(move);
				}
				else {
					//move to player origin
					move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));
					updatePosition(move);
				}



				//update hitbox
				getHitBox().updateHitBox(getOrigin(), getWidth()* sizeAlter, getWidth()* sizeAlter, getHeight()* sizeAlter, getHeight()* sizeAlter); //explosion size can be set by the creating spell



			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}



				//play explosion animation, enable collision on a certain frame
				if (currentAnimationFrame == 6) {
					collisionFrame = true;
				}
				else
				{
					collisionFrame = false;
				}

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = AIR_SPIKE_ANIMATION_TIMER;
					currentAnimationFrame++;

					//destroy explosion at end of animation
					if (currentAnimationFrame > animationFrames) {
						kill();
					}
				}





				//only check collision on the collisionFrame
				if (collisionFrame && !dealtDamage) {

					//COLLISION CHECK
					if (!queue.empty())
					{
						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {



								//deal damage
								float explosionDamage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * AIR_SPIKE_DAMAGE_MULT;
								dynamic_cast<Enemy*>(itr->second)->alterHealth(-(explosionDamage));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.35f, SpellID::knockback));
								dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(glm::normalize(itr->second->getOrigin() - dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));

								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(2.5f, SpellID::EarthAir));

								dealtDamage = true;
								//printf("PLAYER IS COLLIDING WITH ENEMY\n");
								//break;




							}
						}



					}
				}








			}




			break;
		}

		case SpellID::AirAir: {
			/*
			apply the stacking swift speed II buff, kill this spell

			*/
			
			/*
			float blinkDistance = 0.1f;

			if (dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft()) {
				glm::mat4 move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin() + glm::vec3(0.1f, 0.0f, 0.0f)));
				dynamic_cast<Player*>(getGame()->getPlayer())->updatePosition(move);
			}
			else
			{
				glm::mat4 move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin() - glm::vec3(0.1f, 0.0f, 0.0f)));
				dynamic_cast<Player*>(getGame()->getPlayer())->updatePosition(move);
			}
			
			*/
			

			


			dynamic_cast<Player*>(getGame()->getPlayer())->addBuff(spellBuff(duration, ID));
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

			//remove this buff if it already exists
			dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::FireFireFire);
			
			//apply a fresh stack
			dynamic_cast<Player*>(getGame()->getPlayer())->addBuff(spellBuff(duration, ID));


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


			glm::mat4 move;
			float alterSizeW = 0.75f;
			float alterSizeH = 0.525f;
			float xDistance = getWidth() + 0.075f;

			if (firstUpdate) {
				//do first update things
				firstUpdate = false;

				if (dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft()) {
					move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin() - glm::vec3(xDistance, 0.0f, 0.0f)));
					updatePosition(move);
				}
				else
				{
					move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin() + glm::vec3(xDistance,0.0f,0.0f)));
					updatePosition(move);
				}

				

				//update hitbox
				getHitBox().updateHitBox(getOrigin(), getWidth() * alterSizeW, getWidth()* alterSizeW, getHeight()* alterSizeH, getHeight()* alterSizeH); //explosion size can be set by the creating spell


			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}


				//play explosion animation, enable collision on a certain frame


				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = BARRAGE_ANIMATION_TIMER;
					currentAnimationFrame++;

					//destroy explosion at end of animation
					if (currentAnimationFrame > animationFrames) {
						currentAnimationFrame = 5;
					}
				}





				if (damageTimer <= 0.0f)
				{

					//COLLISION CHECK
					if (!queue.empty())
					{
						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {


								//deal damage
								float damage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * BARRAGE_DAMAGE_MULT;
								dynamic_cast<Enemy*>(itr->second)->alterHealth(-(damage));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.09f, SpellID::knockback));
								dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(glm::normalize(itr->second->getOrigin() - 
									dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));

								damageTimer = 0.1f; //can deal damage every seconds

								//printf("PLAYER IS COLLIDING WITH ENEMY\n");
								//break;




							}
						}



					}

				}


				damageTimer -= dt;



				duration -= dt;
				if (duration <= 0.0f) {
					kill();
				}



			}





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


			glm::mat4 move;
			//float alterSizeW = 0.75f;
			//float alterSizeH = 0.525f;

			if (firstUpdate) {
				//do first update things
				firstUpdate = false;

				
				move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));
				updatePosition(move);
				
				FIND_ENEMY = true;

				resize(GOLEM_WALKING_WIDTH, GOLEM_WALKING_HEIGHT);

			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}

				

				closestEnemy = nullptr;

				//play explosion animation, enable collision on a certain frame

					float smallestDistance = 10000.0f;
					float checkDistance = 0.0f;
					

					//search for nearest enemy here set location of this spell to that enemy's origin

					if (!queue.empty())
					{
						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							if (itr->second->renderOrder == 3 && !itr->second->shouldDestroy()) {
								
								if (dynamic_cast<Enemy*>(itr->second)->getAlive())
								{


									checkDistance = glm::length(dynamic_cast<Enemy*>(itr->second)->getOrigin() - getOrigin());

									if (checkDistance < smallestDistance) {
										smallestDistance = checkDistance;
										closestEnemy = itr->second;
									}
								}
							}



						}

					}


					/*
					flipTimer -= dt;

					if (flipTimer <= 0.0f) {
						
						flipTimer = FLIP_TIME;
					}
					*/
					
					if (closestEnemy != nullptr) {

							if ((dynamic_cast<Enemy*>(closestEnemy)->getOrigin().x < getOrigin().x)) {
								flipped = true;
							
							}

							if ((dynamic_cast<Enemy*>(closestEnemy)->getOrigin().x >= getOrigin().x)) {
								flipped = false;
							
							}
						





							if (animationTimer > 0.0f) {
								animationTimer -= dt;



							}
							else
							{



								currentAnimationFrame++;



								if (WALKING) {
									animationFrames = 4;
									animationTimer = GOLEM_WALKING_ANIMATION_TIMER;

									//destroy explosion at end of animation
									if (currentAnimationFrame > animationFrames) {
										currentAnimationFrame = 0;

									}
								}

								if (ATTACKING) {
									animationFrames = 10;
									animationTimer = GOLEM_FIRE_ATTACK_TIMER;



									if (currentAnimationFrame > animationFrames) {
										currentAnimationFrame = 0;
										ATTACKING = false;
										WALKING = true;

										if (glm::length(dynamic_cast<Enemy*>(closestEnemy)->getOrigin() - getOrigin()) < 0.09f) {
											WALKING = false;
											ATTACKING = true;

										}
									}

									if (currentAnimationFrame == 4 || currentAnimationFrame == 8) {
										collisionFrame = true;
									}
									else
									{
										collisionFrame = false;
									}


								}



							}






							if (ATTACKING) {
								//printf("%d\n", flipped);
								damageTimer -= dt;

								resize(GOLEM_ATTACKING_WIDTH, GOLEM_ATTACKING_HEIGHT);
								getHitBox().updateHitBox(getOrigin(), getWidth(), getWidth(), getHeight() * 1.25f, getHeight() * 1.25f); //explosion size can be set by the creating spell


								if (damageTimer <= 0.0f && collisionFrame)
								{

									//COLLISION CHECK
									if (!queue.empty())
									{
										for (itr = queue.begin(); itr != queue.end(); ++itr) {

											//checks collision with ENEMY renderable in the queue
											if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {




												//deal damage
												float damage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * FIRE_GOLEM_DAMAGE_MULT;
												dynamic_cast<Enemy*>(itr->second)->alterHealth(-(damage));
												dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.3f, SpellID::knockback));
												dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(glm::normalize(itr->second->getOrigin() -
													dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));

												damageTimer = 0.15f; //can deal damage every seconds

												//printf("PLAYER IS COLLIDING WITH ENEMY\n");
												//break;




											}
										}



									}

								}



							}


							if (WALKING) {
								//move
								if (closestEnemy != nullptr) {




									direction = glm::normalize(dynamic_cast<Enemy*>(closestEnemy)->getOrigin() - getOrigin());
									move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * moveSpeed * dt, direction.y * moveSpeed * dt, 0.0f));
									updatePosition(move);



									//update hitbox
									resize(GOLEM_WALKING_WIDTH, GOLEM_WALKING_HEIGHT);

									getHitBox().updateHitBox(getOrigin(), getWidth(), getWidth(), getHeight(), getHeight()); //explosion size can be set by the creating spell


									if (glm::length(dynamic_cast<Enemy*>(closestEnemy)->getOrigin() - getOrigin()) < 0.09f) {
										WALKING = false;
										ATTACKING = true;
										currentAnimationFrame = 0;

									}


								}

							}









					}





				duration -= dt;
				if (duration <= 0.0f) {
					kill();
				}



			}





			break;
		}
		case SpellID::FireFireAir: {
			/*
			on first update do nothing, 

			on every other update decrement timer, for every 5th of the timer (split timer into 5 parts),
			create an explosion1 at the correct spot in an arc in the direction of the player

			destroy when expired

			*/

			Renderable* createdExplosion = nullptr;
			glm::mat4 move;
			glm::mat4 rotation;
			

			//flip the waterBolt direction if player is facing left
			float angle = 0.0f;

			if (dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft()) {
				direction = glm::vec3(-1.0f, 0.0f, 0.0f);
			}
			else
			{
				direction = glm::vec3(1.0f, 0.0f, 0.0f);
			}

			
			damageTimer -= dt;

			if (damageTimer <= 0.0f) {

				if (dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft()) {
					angle = (-glm::pi<float>()) / 3.0f;

					rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

					direction = rotation * glm::vec4(direction, 0.0f);



					angle = (((2.0 * glm::pi<float>() / 3.0f)) / (static_cast<float>(FIRECRACKER_AMOUNT))) * static_cast<float>(animationFrames);


					//create water bolt and set its direction + random angle
					createdExplosion = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::explosion1), SpellID::Explosion1);

					//angle += (((2.0 * glm::pi<float>() / 3.0f)) / (static_cast<float>(FIRECRACKER_AMOUNT)));

					rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

				}
				else
				{
					angle = (glm::pi<float>()) / 3.0f;




					rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

					direction = rotation * glm::vec4(direction, 0.0f);



					angle = (((2.0 * glm::pi<float>() / 3.0f)) / (static_cast<float>(FIRECRACKER_AMOUNT))) * static_cast<float>(animationFrames);


					//create water bolt and set its direction + random angle
					createdExplosion = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::explosion1), SpellID::Explosion1);

					//angle += (((2.0 * glm::pi<float>() / 3.0f)) / (static_cast<float>(FIRECRACKER_AMOUNT)));

					rotation = glm::rotate(glm::mat4(1.0f), -angle, glm::vec3(0.0f, 0.0f, 1.0f));


				}
				
				

					direction = rotation * glm::vec4(direction, 0.0f);


					move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().x + direction.x / 2.25f,
						dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().y + direction.y / 2.25f, 0.0f));

					dynamic_cast<Spell*>(createdExplosion)->updatePosition(move);

					getGame()->renderableToPendingAdd(createdExplosion);


					damageTimer = FIRECRACKER_TIMER;

					animationFrames++;

					if (animationFrames == FIRECRACKER_AMOUNT) {
						kill();
					}

				
			}



			break;
		}
		case SpellID::FireWaterWater: {
			/*
			Add a stackable heal buff to the player

			*/

			dynamic_cast<Player*>(getGame()->getPlayer())->addBuff(spellBuff(duration, ID));
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


			glm::mat4 move;


			if (firstUpdate) {
				//do first update things
				firstUpdate = false;

				float smallestDistance = 10000.0f;
				float checkDistance = 0.0f;
				Renderable* nearestEnemy = nullptr;

				//search for nearest enemy here set location of this spell to that enemy's origin

				if (!queue.empty())
				{
					for (itr = queue.begin(); itr != queue.end(); ++itr) {

						

							if (itr->second->renderOrder == 3) {
								
								if (dynamic_cast<Enemy*>(itr->second)->getAlive())
								{

									checkDistance = glm::length(dynamic_cast<Enemy*>(itr->second)->getOrigin() - dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin());

									if (checkDistance < smallestDistance) {
										smallestDistance = checkDistance;
										nearestEnemy = itr->second;
									}
								}
							}

						

					}

				}


				if (nearestEnemy != nullptr) {
					//move to that enemies origin

					if (dynamic_cast<Enemy*>(nearestEnemy)->getOrigin().x < dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().x) {
						flip();
						direction = glm::vec3(-1.0f, 0.0f, 0.0f);

					}

					move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Enemy*>(nearestEnemy)->getOrigin()));
					updatePosition(move);
				}
				else {
					//move to player origin
					move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));
					updatePosition(move);
				}






			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}


				//have the fireball travel
				move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * moveSpeed * dt, 0.0f, 0.0f));
				updatePosition(move);

				float sizeAlter = 0.9f;

				//update hitbox
				getHitBox().updateHitBox(getOrigin(), getWidth()* sizeAlter, getWidth()* sizeAlter, getHeight()* sizeAlter, getHeight()* sizeAlter); //explosion size can be set by the creating spell



				//play explosion animation, enable collision on a certain frame
				if (currentAnimationFrame == 3) {
					collisionFrame = true;
				}
				else
				{
					collisionFrame = false;
				}

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = GEYSER_ANIMATION_TIMER;
					currentAnimationFrame++;

					//destroy explosion at end of animation
					if (currentAnimationFrame > animationFrames) {
						kill();
					}
				}





				//only check collision on the collisionFrame
				if (collisionFrame && !dealtDamage) {

					//COLLISION CHECK
					if (!queue.empty())
					{
						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {



								//deal damage
								float explosionDamage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * GEYSER_DAMAGE_MULT;
								dynamic_cast<Enemy*>(itr->second)->alterHealth(-(explosionDamage));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.75f, SpellID::knockback));
								dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(glm::normalize(itr->second->getOrigin() - dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));

								//dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(2.5f, SpellID::EarthAir));

								dealtDamage = true;
								//printf("PLAYER IS COLLIDING WITH ENEMY\n");
								//break;




							}
						}



					}
				}








			}




			
			break;
		}
		case SpellID::FireWaterAir: {
			/*
			on first update move this spell to be at player's origin with correct direction

			on every other update, move the spell in the direction, update animation, then check if spell has collided with enemies
			if collision, deal damage to that enemy and freeze the enemy

			destroy on collision or out of bounds

			*/


			glm::mat4 move;
			const float xDistance = 0.35f;

			if (firstUpdate) {
				//do first update things
				firstUpdate = false;



					if (dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft()) {
						flip();
						direction = glm::vec3(-1.0f, 0.0f, 0.0f);
						move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().x - xDistance,
							dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().y, 0.0f));
						updatePosition(move);

					}
					else
					{
						move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().x + xDistance,
							dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().y, 0.0f));
						updatePosition(move);
					}


				
			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}


				//have the fireball travel
				move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * moveSpeed * dt, 0.0f, 0.0f));
				updatePosition(move);

				float sizeAlter = 0.95f;

				//update hitbox
				getHitBox().updateHitBox(getOrigin(), getWidth() * sizeAlter, getWidth() * sizeAlter, getHeight() * sizeAlter, getHeight() * sizeAlter); //explosion size can be set by the creating spell



				//play explosion animation, enable collision on a certain frame
				if (currentAnimationFrame == 2) {
					collisionFrame = true;
				}
				else
				{
					collisionFrame = false;
				}

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = FFREEZE_ANIMATION_TIMER;
					currentAnimationFrame++;

					//destroy explosion at end of animation
					if (currentAnimationFrame > animationFrames) {
						kill();
					}
				}





				//only check collision on the collisionFrame
				if (collisionFrame && !dealtDamage) {

					//COLLISION CHECK
					if (!queue.empty())
					{
						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {



								//deal damage
								float explosionDamage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * FFREEZE_DAMAGE_MULT;
								dynamic_cast<Enemy*>(itr->second)->alterHealth(-(explosionDamage));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.5f, SpellID::knockback));
								dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(glm::normalize(itr->second->getOrigin() - dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));

								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(3.25f, ID));

								dealtDamage = true;
								//printf("PLAYER IS COLLIDING WITH ENEMY\n");
								//break;




							}
						}



					}
				}








			}





			break;
		}
		case SpellID::FireEarthEarth: {
			/*
			on first update, set timer to handle spawning meteor cooldown 

			on every other update, check if meteor cooldown in 0,
			if it is, create a meteor  in a random spot around the player

			destroy when duration timer expires

			*/


			Renderable* createdMeteor = nullptr;
			glm::mat4 move;
			glm::mat4 rotation;


			//flip the waterBolt direction if player is facing left
			float angle = 0.0f;
			float distance = 0.0f;
			

			damageTimer -= dt;

			if (damageTimer <= 0.0f) {

				
				//create a random angle and rotate the base direction by that angle and normalize and then use that to spawn meteor
				direction = glm::vec3(1.0f, 0.0f, 0.0f);

				floatDistribution = std::uniform_real_distribution<float>(0.0f, (glm::pi<float>()));

				angle = floatDistribution(getGame()->getNumberEngine());

				rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

				direction = glm::normalize(rotation * glm::vec4(direction, 0.0f));
				
				createdMeteor = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::meteor), SpellID::Meteor);
				
				


				floatDistribution = std::uniform_real_distribution<float>(0.85f, 2.5f);
				distance = floatDistribution(getGame()->getNumberEngine());


				move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().x + direction.x / distance,
					dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().y + direction.y / distance, 0.0f));

				dynamic_cast<Spell*>(createdMeteor)->updatePosition(move);

				getGame()->renderableToPendingAdd(createdMeteor);


				damageTimer = METEOR_BARRAGE_TIMER;

				//animationFrames++;

				


			}

			duration -= dt;

			if (duration <= 0.0f) {
				kill();
			}

			break;
		}
		case SpellID::FireEarthAir: {
			/*
			on first update , move this spell in front of the player

			on every other update, check if the mine has collided with an enemy,
			if it has kill the mine and create an explosion at that point

			*/

			glm::mat4 move;


			if (firstUpdate) {
				//do first update things
				move = glm::translate(glm::mat4(1.0f), dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin());

				updatePosition(move);

				//flip the fireball if player is facing left
				if (dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft())
				{
					flip();
					flipped = true;
					direction = glm::vec3(-1.0f, 0.0f, 0.0f);
				}


				firstUpdate = false;
			}
			else
			{
				//initially the fireball cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}




				//lifetime of spell
				duration -= dt;
				if (duration <= 0.0f) {
					kill();
				}
				else if (duration < EARTH_MINE_DURATION - 0.65f) {
					//no movement
				}
				else
				{
					//moves slowly and updates hitbox
					//have the fireball travel
					move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * moveSpeed * dt, 0.0f, 0.0f));
					updatePosition(move);


					//update hitbox
					getHitBox().updateHitBox(getOrigin(), FIREBALL_WIDTH, FIREBALL_WIDTH, FIREBALL_HEIGHT, FIREBALL_HEIGHT);

				}







				//play fireball animation
				if (currentAnimationFrame > animationFrames) {
					currentAnimationFrame = 0;
				}

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = EARTH_MINE_ANIMATION_TIME;
					currentAnimationFrame++;

					if (currentAnimationFrame > animationFrames) {
						currentAnimationFrame = 0;
					}
				}

				




				//check collisions here, if collision, destroy this spell and create an explosion spell at that point

			//COLLISION CHECK
				if (!queue.empty())
				{
					Renderable* createdExplosion = nullptr;


					for (itr = queue.begin(); itr != queue.end(); ++itr) {

						//checks collision with ENEMY renderable in the queue
						if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {



							//deal fireball damage
							float fireballDamage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * EARTH_MINE_DAMAGE_MULT;
							dynamic_cast<Enemy*>(itr->second)->alterHealth(-(fireballDamage));
							//dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.15f, SpellID::knockback));
							//dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(direction);




							//resize the explosion?

							//create an explosion at this fireball's origin
							createdExplosion = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::explosion1), SpellID::Explosion1);
							move = glm::translate(glm::mat4(1.0f), getOrigin());
							createdExplosion->updatePosition(move);

							getGame()->renderableToPendingAdd(createdExplosion);

							//destroy fireball
							kill();


							//printf("PLAYER IS COLLIDING WITH ENEMY\n");
							//break;

						}

					}


				}




			}






			break;
		}
		case SpellID::FireAirAir: {
			/*
			on first update, set timer to handle spawning fire column cooldown

			on every other update, check if column cooldown in 0,
			if it is, create a column  in a random spot around the player, reset timer

			destroy when duration timer expires

			*/


			Renderable* createdPillar = nullptr;
			glm::mat4 move;
			glm::mat4 rotation;


			//flip the waterBolt direction if player is facing left
			float angle = 0.0f;
			float distance = 0.0f;


			damageTimer -= dt;

			if (damageTimer <= 0.0f) {


				//create a random angle and rotate the base direction by that angle and normalize and then use that to spawn meteor
				direction = glm::vec3(1.0f, 0.0f, 0.0f);

				floatDistribution = std::uniform_real_distribution<float>(0.0f, (2.0f * glm::pi<float>()));

				angle = floatDistribution(getGame()->getNumberEngine());

				rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

				direction = glm::normalize(rotation * glm::vec4(direction, 0.0f));

				createdPillar = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::fire_beam), SpellID::FirePillar);




				floatDistribution = std::uniform_real_distribution<float>(0.9f, 2.5f);
				distance = floatDistribution(getGame()->getNumberEngine());


				move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().x + direction.x / distance,
					dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().y + direction.y / distance, 0.0f));

				dynamic_cast<Spell*>(createdPillar)->updatePosition(move);

				getGame()->renderableToPendingAdd(createdPillar);


				damageTimer = FIRE_STORM_TIMER;

				//animationFrames++;




			}

			duration -= dt;

			if (duration <= 0.0f) {
				kill();
			}

			break;
		}
		case SpellID::WaterWaterWater: {
			/*
			on first update move this spell far away in the direction of the player

			on every other update, update the animation of the spell,
			on collision frame, deal TONS of damage to enemies hit

			destroy when animation ends

			*/


			glm::mat4 move;
			////float alterSizeW = 0.75f;
			//float alterSizeH = 0.525f;

			if (firstUpdate) {
				//do first update things
				firstUpdate = false;

				if (dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft()) {
					flip();
					move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));
					updatePosition(move);
				}
				else
				{
					move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));
					updatePosition(move);
				}



				//update hitbox
				
				getHitBox().updateHitBox(getOrigin(), getWidth(), getWidth(), getHeight(), getHeight()); //explosion size can be set by the creating spell


			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}

				

				//play explosion animation, enable collision on a certain frame
				if (currentAnimationFrame == 3) {
					collisionFrame = true;
				}
				else
				{
					collisionFrame = false;
				}

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = TSUNAMI_ANIMATION_TIME;
					currentAnimationFrame++;

					//destroy explosion at end of animation
					if (currentAnimationFrame > animationFrames) {
						kill();
					}
				}





				//only check collision on the collisionFrame
				if (collisionFrame && !dealtDamage) {

					//COLLISION CHECK
					if (!queue.empty())
					{
						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {



								//deal damage
								float explosionDamage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * TSUNAMI_DAMAGE_MULT;
								dynamic_cast<Enemy*>(itr->second)->alterHealth(-(explosionDamage));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(1.5f, SpellID::knockback));
								dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(glm::normalize(itr->second->getOrigin() - dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));

								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(5.0f, SpellID::FireWaterAir));

								dealtDamage = true;
								//printf("PLAYER IS COLLIDING WITH ENEMY\n");
								//break;




							}
						}



					}
				}





			}





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



			glm::mat4 move;
			//float alterSizeW = 0.75f;
			//float alterSizeH = 0.525f;

			if (firstUpdate) {
				//do first update things
				firstUpdate = false;


				move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));
				updatePosition(move);

				FIND_ENEMY = true;

				resize(GOLEM_WALKING_WIDTH * WATER_GOLEM_SIZE_MULT, GOLEM_WALKING_HEIGHT * WATER_GOLEM_SIZE_MULT);

			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}



				closestEnemy = nullptr;

				//play explosion animation, enable collision on a certain frame

				float smallestDistance = 10000.0f;
				float checkDistance = 0.0f;


				//search for nearest enemy here set location of this spell to that enemy's origin

				if (!queue.empty())
				{
					for (itr = queue.begin(); itr != queue.end(); ++itr) {

						if (itr->second->renderOrder == 3 && !itr->second->shouldDestroy()) {

							if (dynamic_cast<Enemy*>(itr->second)->getAlive())
							{


								checkDistance = glm::length(dynamic_cast<Enemy*>(itr->second)->getOrigin() - getOrigin());

								if (checkDistance < smallestDistance) {
									smallestDistance = checkDistance;
									closestEnemy = itr->second;
								}
							}
						}



					}

				}


				/*
				flipTimer -= dt;

				if (flipTimer <= 0.0f) {

					flipTimer = FLIP_TIME;
				}
				*/

				if (closestEnemy != nullptr) {

					if ((dynamic_cast<Enemy*>(closestEnemy)->getOrigin().x < getOrigin().x)) {
						flipped = true;

					}

					if ((dynamic_cast<Enemy*>(closestEnemy)->getOrigin().x >= getOrigin().x)) {
						flipped = false;

					}

				}



				if (animationTimer > 0.0f) {
					animationTimer -= dt;



				}
				else
				{



					currentAnimationFrame++;



					if (WALKING) {
						animationFrames = 4;
						animationTimer = GOLEM_WALKING_ANIMATION_TIMER;

						//destroy explosion at end of animation
						if (currentAnimationFrame > animationFrames) {
							currentAnimationFrame = 0;

						}
					}

					if (ATTACKING) {
						animationFrames = 10;
						animationTimer = GOLEM_WATER_ATTACK_TIMER;



						if (currentAnimationFrame > animationFrames) {
							currentAnimationFrame = 0;
							ATTACKING = false;
							WALKING = true;

						}

						if (currentAnimationFrame == 4 || currentAnimationFrame == 8) {
							collisionFrame = true;
						}
						else
						{
							collisionFrame = false;
						}


					}



				}






				if (ATTACKING) {
					//printf("%d\n", flipped);
					damageTimer -= dt;

					resize(GOLEM_ATTACKING_WIDTH * WATER_GOLEM_SIZE_MULT, GOLEM_ATTACKING_HEIGHT* WATER_GOLEM_SIZE_MULT);
					//getHitBox().updateHitBox(getOrigin(), getWidth(), getWidth(), getHeight() * 1.25f, getHeight() * 1.25f); //explosion size can be set by the creating spell


					if (damageTimer <= 0.0f && collisionFrame && closestEnemy != nullptr)
					{

						Renderable* createdBullet = nullptr;
						//spawn bullet at the golems origin towards nearest enemy

						direction = glm::normalize(dynamic_cast<Enemy*>(closestEnemy)->getOrigin() - getOrigin());

						
						float angle = glm::angle(direction, glm::vec3(1.0f, 0.0f, 0.0f));

						if (dynamic_cast<Enemy*>(closestEnemy)->getOrigin().y < getOrigin().y) {
							createdBullet = new Basic_Attack(getGame(), 4, static_cast<int>(SPRITE_SHEETS::basic_attack), -angle, 1.2f);

						}
						else
						{
							createdBullet = new Basic_Attack(getGame(), 4, static_cast<int>(SPRITE_SHEETS::basic_attack), angle, 1.2f);

						}

						


						

						glm::mat4 move = glm::translate(glm::mat4(1.0f), glm::vec3(getOrigin().x, getOrigin().y, 0.0f));

						createdBullet->updatePosition(move);


						getGame()->renderableToPendingAdd(createdBullet);

								
						damageTimer = 0.1f; //can deal damage every seconds

									//printf("PLAYER IS COLLIDING WITH ENEMY\n");
									//break;

						


					}



				}


				if (WALKING) {
					//move
					if (closestEnemy != nullptr) {




						direction = glm::normalize(dynamic_cast<Enemy*>(closestEnemy)->getOrigin() - getOrigin());
						move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * moveSpeed * dt, direction.y * moveSpeed * dt, 0.0f));
						updatePosition(move);



						//update hitbox
						resize(GOLEM_WALKING_WIDTH * WATER_GOLEM_SIZE_MULT, GOLEM_WALKING_HEIGHT * WATER_GOLEM_SIZE_MULT);

						//getHitBox().updateHitBox(getOrigin(), getWidth(), getWidth(), getHeight(), getHeight()); //explosion size can be set by the creating spell


						attackTimer -= dt;

						if (attackTimer <= 0.0f) {
							attackTimer = GOLEM_WATER_ATTACK_TIMER;
							WALKING = false;
							ATTACKING = true;
						}


					}

				}









				duration -= dt;
				if (duration <= 0.0f) {
					kill();
				}



			}




			break;
		}
		case SpellID::WaterWaterAir: {
			/*
			on first update move this spell to be at player's origin with correct direction, COPY CODE TO LOOP THE ANIMATION

			on every other update, move the spell in the direction, update animation, then check if spell has collided with enemies
			if collision, deal damage to that enemy 

			destroy when duration runs out

			*/


			glm::mat4 move;


			if (firstUpdate) {
				//do first update things
				move = glm::translate(glm::mat4(1.0f), dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin());

				updatePosition(move);

				//flip the fireball if player is facing left
				if (dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft())
				{
					flip();
					direction = glm::vec3(-1.0f, 0.0f, 0.0f);
				}


				firstUpdate = false;
			}
			else
			{
				//initially the fireball cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}


				//have the fireball travel
				move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * moveSpeed * dt, 0.0f, 0.0f));
				updatePosition(move);

				float alter = 0.85f;

				//update hitbox
				getHitBox().updateHitBox(getOrigin(), getWidth()* alter, getWidth()* alter, getHeight()* alter, getHeight()* alter);



				//check collisions here, if collision, destroy this spell and create an explosion spell at that point


				damageTimer -= dt;

				



				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = WATER_SPOUT_ANIMATION_TIMER;
					currentAnimationFrame++;

					if (currentAnimationFrame > animationFrames) {
						currentAnimationFrame = 4;
					}
				}


				



				//check collisions here, if collision, destroy this spell and create an explosion spell at that point

				if (damageTimer <= 0.0f) {
					dealtDamage = false;
				}



				//COLLISION CHECK
				if (!queue.empty())
				{

					if (!dealtDamage) {

						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {

								//getHitBox().updateHitBox(getOrigin(), getWidth() * 1.1f, getWidth() * 1.1f, getHeight() * 1.1f, getHeight() * 1.1f);

								//deal fireball damage
								float damage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * WATER_SPOUT_DAMAGE_MULT;
								dynamic_cast<Enemy*>(itr->second)->alterHealth(-(damage));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.5f, SpellID::knockback));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.75f, SpellID::FireWaterAir));
								dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(direction);


								dealtDamage = true;
								damageTimer = WATER_SPOUT_DAMAGE_TIMER;

								//destroy fireball
								//kill();


								//printf("PLAYER IS COLLIDING WITH ENEMY\n");


							}

						}
					}



				}




				//lifetime of spell
				duration -= dt;
				if (duration <= 0.0f) {
					kill();
				}

			}

			
			break;
		}
		case SpellID::WaterEarthEarth: {
			/*
			on first update move this spell to be at player's origin with correct direction, set spawn spike timer

			on every other update, move the spell in the direction, check if timer is 0
			if timer is 0, reset it and create a SMALL earth spike at that location

			destroy when duration ends

			*/

			glm::mat4 move;
			Renderable* createdEarthSpike = nullptr;


			if (firstUpdate) {
				//do first update things
				move = glm::translate(glm::mat4(1.0f), dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin());

				updatePosition(move);

				//flip the fireball if player is facing left
				if (dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft())
				{
					//flip();
					flipped = true;
					direction = glm::vec3(-1.0f, 0.0f, 0.0f);
				}


				firstUpdate = false;
			}
			else
			{
				//initially the fireball cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}


				//have the fireball travel
				move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * moveSpeed * dt, 0.0f, 0.0f));
				updatePosition(move);



				//check collisions here, if collision, destroy this spell and create an explosion spell at that point


				damageTimer -= dt;

				if (damageTimer <= 0.0f) {
					damageTimer = EARTH_WAVE_SPAWN_TIMER;

					createdEarthSpike = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::earth_spike), SpellID::SmallEarthSpike);
					move = glm::translate(glm::mat4(1.0f), getOrigin());
					dynamic_cast<Spell*>(createdEarthSpike)->updatePosition(move);
					dynamic_cast<Spell*>(createdEarthSpike)->setFlipped(flipped);
					getGame()->renderableToPendingAdd(createdEarthSpike);

				}




				//lifetime of spell
				duration -= dt;
				if (duration <= 0.0f) {
					kill();
				}

			}



			break;
		}
		case SpellID::WaterEarthAir: {
			/*
			on first update move this spell far away in the direction of the player

			on every other update, update the animation of the spell,
			on collision frame, deal damage to enemies hit

			destroy when animation ends

			*/


			glm::mat4 move;


			if (firstUpdate) {
				//do first update things
				firstUpdate = false;

				float sizeAlter = 0.5f;
				float xDistance = getWidth() + 0.05f;

				flipped = dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft();

				if (!flipped) {
					move = glm::translate(glm::mat4(1.0f), glm::vec3(
						dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().x + xDistance, dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().y, 0.0f));

				}
				else
				{
					move = glm::translate(glm::mat4(1.0f), glm::vec3(
						dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().x - xDistance, dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().y, 0.0f));
					flip();
				}


				updatePosition(move);

				//update hitbox
				getHitBox().updateHitBox(getOrigin(), getWidth(), getWidth() , getHeight() * sizeAlter, getHeight() * sizeAlter); //explosion size can be set by the creating spell


			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}



				//play explosion animation, enable collision on a certain frame
			

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = WATER_BEAM_ANIMATION_TIMER;
					currentAnimationFrame++;

					//destroy explosion at end of animation
					if (currentAnimationFrame > animationFrames) {
						kill();
					}
				}


				damageTimer -= dt;


				//only check collision on the collisionFrame
				if (damageTimer <= 0.0) {

					//COLLISION CHECK
					if (!queue.empty())
					{



						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {


								//deal damage
								float explosionDamage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * WATER_BEAM_DAMAGE_MULT;
								dynamic_cast<Enemy*>(itr->second)->alterHealth(-(explosionDamage));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.25f, SpellID::knockback));
								dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(glm::normalize(itr->second->getOrigin() - getGame()->getPlayer()->getOrigin()));

								//tell the game to not process anymore possible collisions for this spell
								damageTimer = 0.1f;


							}
						}





					}
				}








			}






			break;
		}
		case SpellID::WaterAirAir: {
			/*
			Add the multishot buff to the player, kill this spell

			*/

			//remove this buff if it already exists
			dynamic_cast<Player*>(getGame()->getPlayer())->removeSpellBuff(SpellID::WaterAirAir);

			//apply a fresh stack
			dynamic_cast<Player*>(getGame()->getPlayer())->addBuff(spellBuff(duration, ID));


			//remove later
			kill();
			break;
		}
		case SpellID::EarthEarthEarth: {
			/*
			create 4 Large Earth Spikes in the four cardinal direction around the player

			destroy this spell

			*/

			glm::mat4 move;
			Renderable* createdEarthSpike = nullptr;



			//COLLISION CHECK
			if (!queue.empty())
			{
				for (itr = queue.begin(); itr != queue.end(); ++itr) {

					//checks collision with ENEMY renderable in the queue
					
					if (itr->second->renderOrder == 3) {

						if (dynamic_cast<Enemy*>(itr->second)->getOrigin().x < dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().x)
						{
							//flip();
							flipped = true;
						}

						//have the fireball travel
						move = glm::translate(glm::mat4(1.0f), dynamic_cast<Enemy*>(itr->second)->getOrigin());




						//check collisions here, if collision, destroy this spell and create an explosion spell at that point

						createdEarthSpike = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::earth_impale), SpellID::BigEarthSpike);

						dynamic_cast<Spell*>(createdEarthSpike)->updatePosition(move);
						dynamic_cast<Spell*>(createdEarthSpike)->setFlipped(flipped);
						getGame()->renderableToPendingAdd(createdEarthSpike);


					}



					
				}



			}

					kill();
				
			break;
		}
		case SpellID::EarthEarthAir: {
			/*
			
				create 8 Saturn rocks

				(these rocks will given themeselves a random distance/angle/rotation speed and will follow the player)

				destroy this spell

			*/


			Renderable* createdRock = nullptr;
			glm::mat4 move;
			glm::mat4 rotation;


			//flip the waterBolt direction if player is facing left
			float angle = 0.0f;
			float distance = 0.0f;


			damageTimer -= dt;

			if (damageTimer <= 0.0f) {

				floatDistribution = std::uniform_real_distribution<float>(0.15f, 0.425f);

				//create a random angle and rotate the base direction by that angle and normalize and then use that to spawn meteor
				direction = glm::vec3(floatDistribution(getGame()->getNumberEngine()), 0.0f, 0.0f);

				floatDistribution = std::uniform_real_distribution<float>(0.0f, (2.0f * glm::pi<float>()));

				angle = floatDistribution(getGame()->getNumberEngine());

				rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

				direction = rotation * glm::vec4(direction, 0.0f);

				createdRock = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::saturn_rock), SpellID::SaturnRock);

				move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().x + direction.x,
					dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().y + direction.y, 0.0f));

				dynamic_cast<Spell*>(createdRock)->updatePosition(move);
				dynamic_cast<Spell*>(createdRock)->setDirection(direction);
				dynamic_cast<Spell*>(createdRock)->setAnimationTimer(angle);
				getGame()->renderableToPendingAdd(createdRock);


				damageTimer = SATURN_ROCK_SPAWN_TIMER;

				//animationFrames++;




			}

			duration -= dt;

			if (duration <= 0.0f) {
				kill();
			}

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



			glm::mat4 move;
			//float alterSizeW = 0.75f;
			//float alterSizeH = 0.525f;

			if (firstUpdate) {
				//do first update things
				firstUpdate = false;


				move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));
				updatePosition(move);

				FIND_ENEMY = true;

				resize(GOLEM_WALKING_WIDTH * AIR_GOLEM_SIZE_MULT, GOLEM_WALKING_HEIGHT * AIR_GOLEM_SIZE_MULT);

			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}



				closestEnemy = nullptr;

				//play explosion animation, enable collision on a certain frame

				float smallestDistance = 10000.0f;
				float checkDistance = 0.0f;


				//search for nearest enemy here set location of this spell to that enemy's origin

				if (!queue.empty())
				{
					for (itr = queue.begin(); itr != queue.end(); ++itr) {

						if (itr->second->renderOrder == 3 && !itr->second->shouldDestroy()) {

							if (dynamic_cast<Enemy*>(itr->second)->getAlive())
							{


								checkDistance = glm::length(dynamic_cast<Enemy*>(itr->second)->getOrigin() - getOrigin());

								if (checkDistance < smallestDistance) {
									smallestDistance = checkDistance;
									closestEnemy = itr->second;
								}
							}
						}



					}

				}


				/*
				flipTimer -= dt;

				if (flipTimer <= 0.0f) {

					flipTimer = FLIP_TIME;
				}
				*/

				if (closestEnemy != nullptr) {

					if ((dynamic_cast<Enemy*>(closestEnemy)->getOrigin().x < getOrigin().x)) {
						flipped = true;

					}

					if ((dynamic_cast<Enemy*>(closestEnemy)->getOrigin().x >= getOrigin().x)) {
						flipped = false;

					}




					if (animationTimer > 0.0f) {
						animationTimer -= dt;



					}
					else
					{



						currentAnimationFrame++;



						if (WALKING) {
							animationFrames = 4;
							animationTimer = GOLEM_WALKING_ANIMATION_TIMER;

							//destroy explosion at end of animation
							if (currentAnimationFrame > animationFrames) {
								currentAnimationFrame = 0;

							}
						}

						if (ATTACKING) {
							animationFrames = 10;
							animationTimer = GOLEM_AIR_ATTACK_TIMER;



							if (currentAnimationFrame > animationFrames) {
								currentAnimationFrame = 0;
								ATTACKING = false;
								WALKING = true;

							}

							if (currentAnimationFrame == 4 || currentAnimationFrame == 8) {
								collisionFrame = true;
							}
							else
							{
								collisionFrame = false;
							}


						}



					}






					if (ATTACKING) {
						//printf("%d\n", flipped);
						damageTimer -= dt;

						resize(GOLEM_ATTACKING_WIDTH * AIR_GOLEM_SIZE_MULT, GOLEM_ATTACKING_HEIGHT * AIR_GOLEM_SIZE_MULT);
						//getHitBox().updateHitBox(getOrigin(), getWidth(), getWidth(), getHeight() * 1.25f, getHeight() * 1.25f); //explosion size can be set by the creating spell


						if (damageTimer <= 0.0f && collisionFrame)
						{

							//spawn bullet at the golems origin towards nearest enemy

							Renderable* createdAirSpike = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::no_texture), SpellID::EarthAir);

							getGame()->renderableToPendingAdd(createdAirSpike);


							damageTimer = 0.25f; //can deal damage every seconds

										//printf("PLAYER IS COLLIDING WITH ENEMY\n");
										//break;




						}



					}


					if (WALKING) {
						//move
						if (closestEnemy != nullptr) {




							direction = glm::normalize(dynamic_cast<Enemy*>(closestEnemy)->getOrigin() - getOrigin());
							move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * moveSpeed * dt, direction.y * moveSpeed * dt, 0.0f));
							updatePosition(move);



							//update hitbox
							resize(GOLEM_WALKING_WIDTH * AIR_GOLEM_SIZE_MULT, GOLEM_WALKING_HEIGHT * AIR_GOLEM_SIZE_MULT);

							//getHitBox().updateHitBox(getOrigin(), getWidth(), getWidth(), getHeight(), getHeight()); //explosion size can be set by the creating spell


							attackTimer -= dt;

							if (attackTimer <= 0.0f) {
								attackTimer = GOLEM_AIR_ATTACK_TIMER;
								WALKING = false;
								ATTACKING = true;
							}


						}

					}
















				}




				duration -= dt;
				if (duration <= 0.0f) {
					kill();
				}



			}




			break;
		}
		case SpellID::AirAirAir: {
			/*
			apply the stacking Swift Speed III buff to the palyer

			destroy this spell

			*/
			
			if (firstUpdate) {
				firstUpdate = false;
				dynamic_cast<Player*>(getGame()->getPlayer())->addBuff(spellBuff(duration, ID));
			}
			else
			{

				

				Renderable* createdWhirlwind = nullptr;
				glm::mat4 move;
				glm::mat4 rotation;


				//flip the waterBolt direction if player is facing left
				float angle = 0.0f;
				float distance = 0.0f;


				damageTimer -= dt;

				if (damageTimer <= 0.0f) {



					closestEnemy = nullptr;

					//play explosion animation, enable collision on a certain frame

					float smallestDistance = 10000.0f;
					float checkDistance = 0.0f;


					//search for nearest enemy here set location of this spell to that enemy's origin

					if (!queue.empty())
					{
						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							if (itr->second->renderOrder == 3 && !itr->second->shouldDestroy()) {

								if (dynamic_cast<Enemy*>(itr->second)->getAlive())
								{


									checkDistance = glm::length(dynamic_cast<Enemy*>(itr->second)->getOrigin() - dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin());

									if (checkDistance < smallestDistance) {
										smallestDistance = checkDistance;
										closestEnemy = itr->second;
									}
								}
							}



						}

					}


					if (closestEnemy != nullptr) {

						//create a random angle and rotate the base direction by that angle and normalize and then use that to spawn meteor
						direction = dynamic_cast<Enemy*>(closestEnemy)->getOrigin() - dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin();


						createdWhirlwind = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::whirlwind), SpellID::Whirlwind);

						move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));

						dynamic_cast<Spell*>(createdWhirlwind)->updatePosition(move);
						dynamic_cast<Spell*>(createdWhirlwind)->setDirection(glm::normalize(direction));
						getGame()->renderableToPendingAdd(createdWhirlwind);


						damageTimer = WHIRLWIND_SPAWN_TIMER;
					}


					//animationFrames++;




				}

				duration -= dt;

				if (duration <= 0.0f) {
					kill();
				}
			}
			
			

			break;
		}










		 /*
		These are the update functions for the spells spawned by the main spells
		*/
		case SpellID::Meteor: {

			glm::mat4 move;
			float sizeAlter = 0.95f;
			Renderable* createdExplosion = nullptr;

			if (firstUpdate) {
				//do first update things
				firstUpdate = false;

				

				

			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}





				//move meteor down for x seconds, when done check collision and spawn explosion at that point

				duration -= dt;

				if (duration > 0.0f) {

					//move down
					direction = glm::vec3(0.0f, -1.0 * moveSpeed * dt, 0.0f);
					glm::mat4 move = glm::translate(glm::mat4(1.0f), direction);
					updatePosition(move);

				}
				else {

					
					//check collision and create explosion/damage
					//update hitbox
					getHitBox().updateHitBox(getOrigin(), getWidth()* sizeAlter, getWidth()* sizeAlter, getWidth()* sizeAlter, getWidth()* sizeAlter); //explosion size can be set by the creating spell



					//COLLISION CHECK
					if (!queue.empty())
					{
						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {



								//deal damage
								float explosionDamage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * METEOR_DAMAGE_MULT;
								dynamic_cast<Enemy*>(itr->second)->alterHealth(-(explosionDamage));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.45f, SpellID::knockback));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(1.75f, SpellID::FireEarthEarth));
								dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(glm::normalize(itr->second->getOrigin() - getOrigin()));

								//dynamic_cast<Enemy*>(itr->second)->addToDamagedBy(this);

								//printf("PLAYER IS COLLIDING WITH ENEMY\n");
								
								createdExplosion = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::explosion1), SpellID::Explosion1);
								move = glm::translate(glm::mat4(1.0f), getOrigin());
								dynamic_cast<Spell*>(createdExplosion)->updatePosition(move);
								getGame()->renderableToPendingAdd(createdExplosion);
								
								//break;




							}
						}


					}


					createdExplosion = new Spell(getGame(), 4, static_cast<int>(SPRITE_SHEETS::explosion1), SpellID::Explosion1);
					move = glm::translate(glm::mat4(1.0f), getOrigin());
					dynamic_cast<Spell*>(createdExplosion)->updatePosition(move);
					getGame()->renderableToPendingAdd(createdExplosion);








					kill();
				}


				





				//play explosion animation, enable collision on a certain frame
			
				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = METEOR_ANIMATION_TIMER;
					currentAnimationFrame++;

					if (currentAnimationFrame > animationFrames) {
						currentAnimationFrame = 0;
					}


				}



			}




			break;
		}
		case SpellID::Explosion1: {

			glm::mat4 move;


			if (firstUpdate) {
				//do first update things
				firstUpdate = false;

				float sizeAlter = 0.75f;

				//flip the fireball if player is facing left
				if (dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft())
				{
					flip();
				}

				//update hitbox
				getHitBox().updateHitBox(getOrigin(), getWidth() * sizeAlter, getWidth() * sizeAlter, getWidth() * sizeAlter, getWidth() * sizeAlter); //explosion size can be set by the creating spell


			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}



				//play explosion animation, enable collision on a certain frame
				if (currentAnimationFrame  ==  1) {
					collisionFrame = true;
				}
				else
				{
					collisionFrame = false;
				}

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = EXPLOSION1_ANIMATION_TIMER;
					currentAnimationFrame++;

					//destroy explosion at end of animation
					if (currentAnimationFrame > animationFrames) {
						kill();
					}
				}


				
				

				//only check collision on the collisionFrame
				if (collisionFrame && !dealtDamage) {

					//COLLISION CHECK
					if (!queue.empty())
					{
						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {
								


										//deal damage
										float explosionDamage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * EXPLOSION1_DAMAGE_MULT;
										dynamic_cast<Enemy*>(itr->second)->alterHealth(-(explosionDamage));
										dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.15f, SpellID::knockback));
										dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(glm::normalize(itr->second->getOrigin() - getOrigin()));

										//dynamic_cast<Enemy*>(itr->second)->addToDamagedBy(this);

										dealtDamage = true;
										//printf("PLAYER IS COLLIDING WITH ENEMY\n");
										//break;
									

								

								}
							}

							

						}
					}

				

				




			}




			break;
		}
		case SpellID::WaterBolt: {



			glm::mat4 move;


			if (firstUpdate) {
				//do first update things
				
				firstUpdate = false;
			}
			else
			{
				//initially the fireball cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}




				//play fireball animation
				if (currentAnimationFrame > animationFrames) {
					currentAnimationFrame = 0;
				}

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = WATERBOLT_ANIMATION_TIMER;
					currentAnimationFrame++;

					if (currentAnimationFrame > animationFrames) {
						currentAnimationFrame = 4;
					}
				}

				//have the fireball travel
				move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * moveSpeed * dt, direction.y * moveSpeed * dt, 0.0f));
				updatePosition(move);


				//update hitbox
				getHitBox().updateHitBox(getOrigin(), WATERBOLT_HEIGHT, WATERBOLT_HEIGHT, WATERBOLT_HEIGHT, WATERBOLT_HEIGHT);





				//check collisions here, if collision, destroy this spell and create an explosion spell at that point

			//COLLISION CHECK
				if (!queue.empty())
				{
					


					for (itr = queue.begin(); itr != queue.end(); ++itr) {

						//checks collision with ENEMY renderable in the queue
						if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {



							//deal fireball damage
							float damage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * WATERBOLT_DAMAGE_MULT;
							dynamic_cast<Enemy*>(itr->second)->alterHealth(-(damage));
							dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.65f, SpellID::knockback));
							dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(direction);




							//destroy fireball
							kill();


							//printf("PLAYER IS COLLIDING WITH ENEMY\n");
							//break;

						}

					}


				}




				//lifetime of spell
				duration -= dt;
				if (duration <= 0.0f) {
					kill();
				}

			}






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

			glm::mat4 move;


			if (firstUpdate) {
				//do first update things
				firstUpdate = false;

				float sizeAlter = 0.95f;

				//update hitbox
				getHitBox().updateHitBox(getOrigin(), getWidth() * sizeAlter, getWidth() * sizeAlter, getHeight() * sizeAlter, getHeight() * sizeAlter); //explosion size can be set by the creating spell


			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}



				//play explosion animation, enable collision on a certain frame
				if (currentAnimationFrame == 1) {
					collisionFrame = true;
				}
				else
				{
					collisionFrame = false;
				}

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = FIRE_BEAM_ANIMATION_TIMER;
					currentAnimationFrame++;

					//destroy explosion at end of animation
					if (currentAnimationFrame > animationFrames) {
						kill();
					}
				}





				//only check collision on the collisionFrame
				if (collisionFrame && !dealtDamage) {

					//COLLISION CHECK
					if (!queue.empty())
					{
						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {



								//deal damage
								float explosionDamage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * FIRE_BEAM_DAMAGE_MULT;
								dynamic_cast<Enemy*>(itr->second)->alterHealth(-(explosionDamage));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.225f, SpellID::knockback));
								dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(glm::normalize(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin() - getOrigin()));

								//dynamic_cast<Enemy*>(itr->second)->addToDamagedBy(this);

								dealtDamage = true;
								//printf("PLAYER IS COLLIDING WITH ENEMY\n");
								//break;




							}
						}



					}
				}








			}




			break;
		}
		case SpellID::SmallEarthSpike: {


			if (firstUpdate) {
				//do first update things
				firstUpdate = false;

				float sizeAlter = 0.95f;

				//update hitbox
				getHitBox().updateHitBox(getOrigin(), getWidth() * sizeAlter, getWidth() * sizeAlter, getHeight() * sizeAlter, getHeight() * sizeAlter); //explosion size can be set by the creating spell

				if (flipped) {
					flip();
				}

			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}

				

				//play explosion animation, enable collision on a certain frame
				if (currentAnimationFrame == 0) {
					collisionFrame = true;
				}
				else
				{
					collisionFrame = false;
				}

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = EARTH_WAVE_ANIMATION_TIMER;
					currentAnimationFrame++;

					//destroy explosion at end of animation
					if (currentAnimationFrame > animationFrames) {
						kill();
					}
				}





				//only check collision on the collisionFrame
				if (collisionFrame && !dealtDamage) {

					//COLLISION CHECK
					if (!queue.empty())
					{
						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {



								//deal damage
								float explosionDamage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * EARTH_WAVE_DAMAGE_MULT;
								dynamic_cast<Enemy*>(itr->second)->alterHealth(-(explosionDamage));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(1.5f, SpellID::knockback));
								dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(glm::normalize( dynamic_cast<Enemy*>(itr->second)->getOrigin() - 
									dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));

								//dynamic_cast<Enemy*>(itr->second)->addToDamagedBy(this);

								dealtDamage = true;
								//printf("PLAYER IS COLLIDING WITH ENEMY\n");
								//break;




							}
						}



					}
				}








			}




			break;
		}
		case SpellID::BigEarthSpike: {


			if (firstUpdate) {
				//do first update things
				firstUpdate = false;

				float sizeAlter = 0.95f;

				//update hitbox
				getHitBox().updateHitBox(getOrigin(), getWidth() * sizeAlter, getWidth() * sizeAlter, getHeight() * sizeAlter, getHeight() * sizeAlter); //explosion size can be set by the creating spell

				if (flipped) {
					flip();
				}

			}
			else
			{
				//initially the explosion cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}



				//play explosion animation, enable collision on a certain frame
				if (currentAnimationFrame == 3) {
					collisionFrame = true;
				}
				else
				{
					collisionFrame = false;
				}

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = FISSURE_ANIMATION_TIMER;
					currentAnimationFrame++;

					//destroy explosion at end of animation
					if (currentAnimationFrame > animationFrames) {
						kill();
					}
				}





				//only check collision on the collisionFrame
				if (collisionFrame && !dealtDamage) {

					//COLLISION CHECK
					if (!queue.empty())
					{
						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {



								//deal damage
								float explosionDamage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * FISSURE_DAMAGE_MULT;
								dynamic_cast<Enemy*>(itr->second)->alterHealth(-(explosionDamage));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(1.75f, SpellID::knockback));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(1.5f, SpellID::EarthEarth));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(5.0f, ID));
								dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(glm::normalize(dynamic_cast<Enemy*>(itr->second)->getOrigin() -
									dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin()));

								//dynamic_cast<Enemy*>(itr->second)->addToDamagedBy(this);

								dealtDamage = true;
								//printf("PLAYER IS COLLIDING WITH ENEMY\n");
								//break;




							}
						}



					}
				}








			}




			break;
		}
		case SpellID::SaturnRock: {


			glm::mat4 move;
			glm::mat4 rotation;

			if (firstUpdate) {
				//do first update things


				std::uniform_int_distribution<int> clock(0, 1);

				//create random rotation speed for rock texture, and for orbiting player
				floatDistribution = std::uniform_real_distribution<float>(1.5f, 2.5f);
				moveSpeed = SATURN_ROCK_BASE_ROTATION_SPEED * floatDistribution(getGame()->getNumberEngine());
				
				int i = clock(getGame()->getNumberEngine());

				if (i == 1) {
					moveSpeed *= -1.0f;
				}

				damageTimer = 0.0f;
				firstUpdate = false;
			}
			else
			{
				//initially the fireball cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}



				//move in circle around player
				setOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
				setO2W(glm::mat4(1.0f));
				resize(SATURN_ROCK_WIDTH, SATURN_ROCK_HEIGHT);


				//have the fireball travel
				
					
				rotation = glm::rotate(glm::mat4(1.0f), moveSpeed, glm::vec3(0.0f, 0.0f, 1.0f));

				direction = rotation * glm::vec4(direction, 0.0f);

				move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().x + direction.x,
					dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin().y + direction.y, 0.0f));

				updatePosition(move);


				





				//update hitbox
				getHitBox().updateHitBox(getOrigin(), SATURN_ROCK_WIDTH, SATURN_ROCK_WIDTH, SATURN_ROCK_HEIGHT, SATURN_ROCK_HEIGHT);





				//check collisions here, if collision, destroy this spell and create an explosion spell at that point

				damageTimer -= dt;
				if (damageTimer <= 0.0f) {


					//COLLISION CHECK
					if (!queue.empty())
					{



						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {

								if (dynamic_cast<Enemy*>(itr->second)->getAlive()) {


									//deal fireball damage
									float damage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * SATURN_ROCK_DAMAGE_MULT;
									dynamic_cast<Enemy*>(itr->second)->alterHealth(-(damage));
									dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.65f, SpellID::knockback));
									dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(direction);


									damageTimer = 0.1f;

								}



							}

						}


					}
				}





				//lifetime of spell
				duration -= dt;
				if (duration <= 0.0f) {
					kill();
				}

			}






			break;
		}

		case SpellID::Whirlwind: {


			glm::mat4 move;


			if (firstUpdate) {
				//do first update things

				firstUpdate = false;
			}
			else
			{
				//initially the fireball cannot collide since it is at the origin, so set it to collidable after first frame
				if (!getCanCollide()) {
					setCanCollide(true);
				}




				//play fireball animation
				if (currentAnimationFrame > animationFrames) {
					currentAnimationFrame = 0;
				}

				if (animationTimer > 0.0f) {
					animationTimer -= dt;
				}
				else
				{
					animationTimer = WHIRLWIND_ANIMATION_TIMER;
					currentAnimationFrame++;

					if (currentAnimationFrame > animationFrames) {
						currentAnimationFrame = 5;
					}
				}

				//have the fireball travel
				move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * moveSpeed * dt, direction.y * moveSpeed * dt, 0.0f));
				updatePosition(move);


				//update hitbox
				getHitBox().updateHitBox(getOrigin(), WHIRLWIND_WIDTH, WHIRLWIND_WIDTH, WHIRLWIND_HEIGHT, WHIRLWIND_HEIGHT);





				//check collisions here, if collision, destroy this spell and create an explosion spell at that point

			//COLLISION CHECK
				damageTimer -= dt;
				if (damageTimer <= 0.0f) {


					if (!queue.empty())
					{



						for (itr = queue.begin(); itr != queue.end(); ++itr) {

							//checks collision with ENEMY renderable in the queue
							if (itr->second->getCanCollide() && checkCollision(itr->second, 3)) {



								//deal fireball damage
								float damage = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentAttack() * WHIRLWIND_DAMAGE_MULT;
								dynamic_cast<Enemy*>(itr->second)->alterHealth(-(damage));
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.85f, SpellID::knockback));
								dynamic_cast<Enemy*>(itr->second)->setKnockbackDirection(direction);

								damageTimer = 0.25f;


								//destroy fireball
								//kill();


								//printf("PLAYER IS COLLIDING WITH ENEMY\n");
								//break;

							}

						}


					}

				}




				//lifetime of spell
				duration -= dt;
				if (duration <= 0.0f) {
					kill();
				}

			}






			break;
		}


	}
}


void Spell::render() {

	//this prevents that spell from appearing at the origin on the first frame
	if (!firstUpdate) {



		//only add spells that will be rendered
		switch (ID) {
		case SpellID::FireFire: {
				renderThisSpell(static_cast<float>(1.0f / 3.0f));//8 frames
				break;
			}
		case SpellID::FireWater: {
			renderThisSpell(static_cast<float>(1.0f / 8.0f));//8 frames
			break;
		}
		case SpellID::WaterAir: {
			renderThisSpell(static_cast<float>(1.0f / 9.0f));//8 frames
			break;
		}
		case SpellID::WaterEarth: {
			renderThisSpell(1.0f);//8 frames
			break;
		}
		case SpellID::FireEarth: {
			renderThisSpell(0.25f);//4 frames
			break;
		}
		case SpellID::EarthEarth: {
			renderThisSpell(static_cast<float>(1.0f / 3.0f));//4 frames
			break;
		}
		case SpellID::EarthAir: {
			renderThisSpell(static_cast<float>(1.0f / 11.0f));//4 frames
			break;
		}
		case SpellID::FireWaterEarth: {
			renderThisSpell(static_cast<float>(1.0f / 15.0f));//4 frames
			break;
		}
		case SpellID::FireFireWater: {
			renderThisSpell(static_cast<float>(1.0f / 8.0f));//4 frames
			break;
		}
		case SpellID::FireFireEarth: {
			if (flipped) {
				flip();
			}
			
			if (WALKING) {
				
				
				setTexture(static_cast<int>(SPRITE_SHEETS::fire_golem_walking));
				renderThisSpell(static_cast<float>(1.0f / 5.0f));//4 frames
			}
			if (ATTACKING) {
				if (flipped) {
					flip();
					setTexture(static_cast<int>(SPRITE_SHEETS::fire_golem_attacking_left));
					renderThisSpell(static_cast<float>(1.0f / 11.0f));//4 frames
				}
				else
				{
					setTexture(static_cast<int>(SPRITE_SHEETS::fire_golem_attacking));
					renderThisSpell(static_cast<float>(1.0f / 11.0f));//4 frames
				}
				
				
			}


			break;
		}
		case SpellID::WaterWaterEarth: {
			if (flipped) {
				flip();
			}

			if (WALKING) {


				setTexture(static_cast<int>(SPRITE_SHEETS::water_golem_walking));
				renderThisSpell(static_cast<float>(1.0f / 5.0f));//4 frames
			}
			if (ATTACKING) {
				if (flipped) {
					flip();
					setTexture(static_cast<int>(SPRITE_SHEETS::water_golem_attacking_left));
					renderThisSpell(static_cast<float>(1.0f / 11.0f));//4 frames
				}
				else
				{
					setTexture(static_cast<int>(SPRITE_SHEETS::water_golem_attacking));
					renderThisSpell(static_cast<float>(1.0f / 11.0f));//4 frames
				}


			}


			break;
		}
		case SpellID::EarthAirAir: {
			if (flipped) {
				flip();
			}

			if (WALKING) {


				setTexture(static_cast<int>(SPRITE_SHEETS::air_golem_walking));
				renderThisSpell(static_cast<float>(1.0f / 5.0f));//4 frames
			}
			if (ATTACKING) {
				if (flipped) {
					flip();
					setTexture(static_cast<int>(SPRITE_SHEETS::air_golem_attacking_left));
					renderThisSpell(static_cast<float>(1.0f / 11.0f));//4 frames
				}
				else
				{
					setTexture(static_cast<int>(SPRITE_SHEETS::air_golem_attacking));
					renderThisSpell(static_cast<float>(1.0f / 11.0f));//4 frames
				}


			}


			break;
		}
		case SpellID::FireWaterAir: {
			renderThisSpell(static_cast<float>(1.0f / 15.0f));//4 frames
			break;
		}
		case SpellID::FireEarthAir: {
			renderThisSpell(static_cast<float>(1.0f / 10.0f));//4 frames
			break;
		}
		case SpellID::WaterWaterWater: {
			renderThisSpell(static_cast<float>(1.0f / 14.0f));//4 frames
			break;
		}
		case SpellID::WaterEarthAir: {
			renderThisSpell(static_cast<float>(1.0f / 24.0f));//4 frames
			break;
		}
		case SpellID::WaterWaterAir: {
			renderThisSpell(static_cast<float>(1.0f / 12.0f));//4 frames
			break;
		}
		case SpellID::Explosion1: {
			renderThisSpell(static_cast<float>(1.0f / 11.0f));//11 frames
			break;
		}
		case SpellID::Meteor: {
			renderThisSpell(static_cast<float>(1.0f / 5.0f));//11 frames
			break;
		}
		case SpellID::FirePillar: {
			renderThisSpell(static_cast<float>(1.0f / 10.0f));//11 frames
			break;
		}
		case SpellID::WaterBolt: {
			renderThisSpell(static_cast<float>(1.0f / 12.0f));//11 frames
			break;
		}
		case SpellID::SmallEarthSpike: {
			renderThisSpell(static_cast<float>(1.0f / 5.0f));//11 frames
			break;
		}
		case SpellID::BigEarthSpike: {
			renderThisSpell(static_cast<float>(1.0f / 16.0f));//11 frames
			break;
		}
		case SpellID::SaturnRock: {
			renderThisSpell(1.0);//11 frames
			break;
		}
		case SpellID::Whirlwind: {
			renderThisSpell(static_cast<float>(1.0f / 11.0f));//11 frames
			break;
		}
		}

	}











}


void Spell::renderThisSpell(float stride) {



	float left = static_cast<float>((currentAnimationFrame)* stride);
	left += 0.002f;
	//0.002 is a constant here? without it there is clipping issues...

	float right = static_cast<float>((currentAnimationFrame + 1) * stride);
	right -= 0.002f;

	getGame()->setTextureCoordinates(right, 1.0f,
		right, 0.0f,
		left, 0.0f,
		left, 1.0f);


	GLint objectToWorld = glGetUniformLocation(getGame()->getRenderablesProgID(), "objectToWorld");
	if (objectToWorld < 0) printf("couldn't find objectToWorld in shader\n");
	glUniformMatrix4fv(objectToWorld, 1, GL_FALSE, glm::value_ptr(getO2W()));

	glBindTexture(GL_TEXTURE_2D, getTexture());
	glBindVertexArray(getGame()->getVAO());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	getGame()->resetTextureCoordinates();



}


