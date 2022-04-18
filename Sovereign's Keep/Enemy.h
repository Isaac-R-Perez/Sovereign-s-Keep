#pragma once
#include "Character.h"
/*
* Child of the Character class.
* This class is for all enemy types that the
* game will have.
*/
enum class EnemyType {
	slime, bat, crab, minotaur, skull
};

const float ENEMY_WALKING_BASE_TIME = 0.1f;

const float SLIME_WIDTH = 0.04f;
const float SLIME_HEIGHT = 0.04f;
const float SLIME_TIMER = 0.1f;

const float BAT_WIDTH = 0.035f;
const float BAT_HEIGHT = 0.0275f;
const float BAT_TIMER = 0.05f;

const float CRAB_WIDTH = 0.075f;
const float CRAB_HEIGHT = 0.05f;
const float CRAB_TIMER = 0.125f;

const float MINOTAUR_WIDTH = 0.08f;
const float MINOTUAR_HEIGHT = 0.08f;
const  float MINOTAUR_TIMER = 0.03f;

const float SKULL_WIDTH = 0.025f;
const float SKULL_HEIGHT = 0.04f;
const float SKULL_TIMER = 0.8f;



class Enemy: public Character
{
private:
	int soulDrop = 1; //The amount of souls the enemy will drop

	//determines how the enemy acts and renders
	EnemyType type;

	//if false facing right, if true facing left
	bool facingRight;
	bool facingLeft;

	//determines how fast the running animation plays
	float animationTimer;
	int current_frame;

	/*
		KNOCKBACK is possible, just need a buff for it, as well as a direction of the knockback
	*/

	glm::vec3 knockbackDirection;

	//stores the renderables that have damaged this enemy
	//std::vector<Renderable*> damagedBy;



	//a buff as applied this, so stop animation, and set movespeed to 0.0 until stun buff is gone
	bool stunned;

	//a buff as applied this, so stop animation, SET RENDER FLAG TO frozen (blue shifted), and set movespeed to 0.0 until frozen buff is gone
	bool frozen;


public:

	struct stats
	{
		float h, mh, a, d, s;
		stats()
		{
			h = 0.0f;
			mh = 0.0f;
			a = 0.0f;
			d = 0.0f;
			s = 0.0f;
		}
		stats(float health, float mhealth, float atk, float def, float spd) : h(health), mh(mhealth), a(atk), d(def), s(spd) {}
	};

	stats enemyStats;

	Enemy(Game* g, int rOrder, int defaultSpriteSheet, EnemyType Type, stats s);


	void render();
	void update(double dt);


	void setSoulDrop(int amt);
	int getSoulDrop();

	stats getEnemyStats() { return enemyStats; }


	//all buffs are searched and all stats are calculated for this frame
	void applySpellBuffs();

	void setKnockbackDirection(glm::vec3 dir) { knockbackDirection = dir; }

	void WaveBuff(int wave);


	/*
	
	
	bool checkDamagedBy(Renderable* r) {
		if (!damagedBy.empty())
		{
			for (int i = 0; i < damagedBy.size(); i++) {
				if (damagedBy.at(i)->getID() == r->getID()) {
					return true;
				}
			}

			return false;
		}

		return false;
	}

	void addToDamagedBy(Renderable* r) { damagedBy.emplace_back(r); }

	std::vector<Renderable*>& getDamagedBy() { return damagedBy; }

	//removes any null renderables
	void clearDamagedBy() {
		

		if (!damagedBy.empty())
		{
			//remove any renderables that should be destroyed
			for (std::vector<Renderable*>::iterator itr = damagedBy.begin(); itr != damagedBy.end(); ) {

				if (*itr == nullptr) {
					itr = damagedBy.erase(itr);
				}
				else
				{
					++itr;
				}

			}
		}

	}

	*/


	
};

