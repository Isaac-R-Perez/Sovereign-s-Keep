#pragma once
#include "Character.h"
/*
* Child of the Character class.
* This class is for all enemy types that the
* game will have.
*/
enum class EnemyType {
	slime,
};

const float ENEMY_WALKING_BASE_TIME = 0.1f;

const float SLIME_WIDTH = 0.04f;
const float SLIME_HEIGHT = 0.04f;



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
	std::vector<Renderable*> damagedBy;


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

	
};

