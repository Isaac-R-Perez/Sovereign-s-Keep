#include "Spell.h"

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

		case SpellID::Fire: {
			spellName = "Fired Up";
			manaCost = 5.0f;
			castTime = 0.25f;
			break;
		}



		case SpellID::FireWater: {
			spellName = "Steam Blast";
			manaCost = 1.0f;
			castTime = 0.25f;
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
	switch (ID) {
		case SpellID::Fire: {
			//apply fire element buff
		
			printf("\nCasted Fired Up!!! %d\n");

		
			kill();
			break;
		}

		case SpellID::FireWater: {
			
			//this spell creates a blast of steam, so this spell should already have the correct texture, just 
			// move the spell in the casted direction until a limit is reached (timer?), then check for collisions with enemies
			// figure out a way to determine which enemies have already been hit by this spell
			//once timer is up, kill this spell

			printf("\nCasted Steam Blast!!!\n");

			kill();
			break;
		}

	}
}


void Spell::render() {

}


