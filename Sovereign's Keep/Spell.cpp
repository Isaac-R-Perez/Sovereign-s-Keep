#include "Spell.h"
#include "Player.h"
#include "Enemy.h"
#include <cstdio>

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
			manaCost = 25.0f;
			castTime = 0.75f;
			duration = 10.0f;
			animationFrames = 2;
			setTexture(static_cast<int>(SPRITE_SHEETS::flame_ring));
			resize(FLAME_RING_WIDTH, FLAME_RING_HEIGHT);
			break;
		}
		case SpellID::FireWater: {
			spellName = "Steam Blast";
			manaCost = 10.0f;
			castTime = 0.25f;
			animationFrames = 7;
			setTexture(static_cast<int>(SPRITE_SHEETS::steam_blast));
			resize(STEAM_BLAST_WIDTH, STEAM_BLAST_WIDTH);
			break;
		}
		case SpellID::FireEarth: {
			spellName = "Fireball";
			manaCost = 20.0f;
			castTime = 0.6f;
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
			manaCost = 25.0f;
			castTime = 0.25f;
			duration = 15.0f;
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
			castTime = 0.8f;
			duration = 15.0f;
			setTexture(static_cast<int>(SPRITE_SHEETS::mud_pit));
			resize(MUD_WIDTH, MUD_HEIGHT);
			
			break;
		}
		case SpellID::WaterAir: {
			spellName = "Bubble Shot";
			manaCost = 5.0f;
			castTime = 0.1f;
			duration = 1.6f; //lifetime of firebolt
			animationFrames = 8; //firebolt
			setTexture(static_cast<int>(SPRITE_SHEETS::bubble_shot));
			moveSpeed = 0.65f;
			//direction = glm::vec3(1.0f, 0.0f, 0.0f);
			resize(BUBBLE_SHOT_WIDTH, BUBBLE_SHOT_HEIGHT);
			break;
		}

		case SpellID::EarthEarth: {
			spellName = "Boulder Sling";
			manaCost = 25.0f;
			castTime = 0.5f;
			duration = 1.45f; //lifetime of firebolt
			animationFrames = 2; //firebolt
			setTexture(static_cast<int>(SPRITE_SHEETS::boulder_shot));
			moveSpeed = 0.75f;
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
			duration = 15.0f;
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
			duration = 15.0f;
			break;
		}
		case SpellID::FireWaterEarth: {
			spellName = "Geyser";
			manaCost = 35.0f;
			castTime = 0.4f;
			animationFrames = 14; //firebolt
			moveSpeed = 0.03f;
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
			setTexture(static_cast<int>(SPRITE_SHEETS::geyser));
			resize(GEYSER_HEIGHT, GEYSER_HEIGHT);
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
			duration = 10.0f;
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
			duration = 7.0f;
			break;
		}
		case SpellID::WaterEarthEarth: {
			spellName = "Earth Wave";
			manaCost = 45.0f;
			castTime = 0.75f;
			duration = 5.0f;
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
			duration = 8.0f;
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
			duration = 20.0f;
			break;
		}


/*
	These spell IDs are for spells spawned by the main spells
*/
		case SpellID::Meteor: {

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

								damageTimer = 0.55f; //can deal damage every 1 second

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
				float xDistance = 0.3f;

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
									dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(0.75f, SpellID::knockback));
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
								
								dynamic_cast<Enemy*>(itr->second)->addBuff(spellBuff(5.0f, SpellID::WaterEarth));

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
								damageTimer = 0.3f;

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

				float sizeAlter = 0.8f;
				float smallestDistance = 10000.0f;
				float checkDistance = 0.0f;
				Renderable* nearestEnemy = nullptr;

				//search for nearest enemy here set location of this spell to that enemy's origin

				if (!queue.empty())
				{
					for (itr = queue.begin(); itr != queue.end(); ++itr) {

						if (itr->second->renderOrder == 3) {
							checkDistance = glm::length(dynamic_cast<Enemy*>(itr->second)->getOrigin() - dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin());

							if (checkDistance < smallestDistance) {
								smallestDistance = checkDistance;
								nearestEnemy = itr->second;
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
			float alterSizeW = 0.7f;
			float alterSizeH = 0.6f;

			if (firstUpdate) {
				//do first update things
				firstUpdate = false;

				if (dynamic_cast<Player*>(getGame()->getPlayer())->getFacingLeft()) {
					move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin() - glm::vec3(0.275f, 0.0f, 0.0f)));
					updatePosition(move);
				}
				else
				{
					move = glm::translate(glm::mat4(1.0f), glm::vec3(dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin() + glm::vec3(0.275f,0.0f,0.0f)));
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
							checkDistance = glm::length(dynamic_cast<Enemy*>(itr->second)->getOrigin() - dynamic_cast<Player*>(getGame()->getPlayer())->getOrigin());

							if (checkDistance < smallestDistance) {
								smallestDistance = checkDistance;
								nearestEnemy = itr->second;
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
			dynamic_cast<Player*>(getGame()->getPlayer())->addBuff(spellBuff(duration, ID));

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

			glm::mat4 move;


			if (firstUpdate) {
				//do first update things
				firstUpdate = false;

				float sizeAlter = 0.75f;

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
		case SpellID::Explosion1: {
			renderThisSpell(static_cast<float>(1.0f / 11.0f));//11 frames
			break;
		}
		case SpellID::WaterBolt: {
			renderThisSpell(static_cast<float>(1.0f / 12.0f));//11 frames
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


