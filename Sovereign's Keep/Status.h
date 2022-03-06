#pragma once
/*
* This class will be responsible for applying different
* types of statuses to the Character class.
* STATUS: Burning, Wet, Chilled, Frozen, Conductive, Stunned
*/
class Status
{
private:
	float duration = 0.0;
	float DOT = 0.0; //Damage over time

	bool Burning = false;
	bool Wet = false;
	bool Chilled = false;
	bool Frozen = false;
	bool Conductive = false;
	bool Stunned = false;
	bool Normal = true;

public:
	void setNormal();
	void setBurning();
	void setWet();
	void setChilled();
	void setFrozen();
	void setConductive();
	void setStunned();

	float getDuration();
	void setDuration(float amt);

	float getDOT();

	bool isNormal();
	bool isBurning();
	bool isWet();
	bool isChilled();
	bool isFrozen();
	bool isConductive();
	bool isStunned();
};

/*
* BURNING:
* >Applied when hit wit a FIRE attack
* >Character takes damage over time.
* >BURNING removed if character is hit with a WATER attack.
* >Character's airRES increase to 1.5 so they take 50% more damage from AIR attacks.
* 
* WET:
* >Applied when hit with a WATER attack
* >Character's electrictyRES increased to 1.5.
* >WET removed when hit with an ICE attack. Replaced with FROZEN instead.
* >WET removed when hit with a ELECTRICTY attack. Replaced with STUNNED instead.
* >WET removed when hit with a FIRE attack.
* 
* CHILLED:
* >Applied when hit with and ICE attack
* >Slows the movement speed (moveSpeed) of the Character
* >Character airRES increased to 1.5.
* >CHILLED removed when hit with a WATER attack. Replaced with FROZEN instead.
* >CHILLED removed when hit with a FIRE attack.
* 
* FROZEN:
* >Applied when hit with both WATER and ICE attacks. (See WET and CHILLED)
* >Character can not move while FROZEN.
* >Character earthRES increased to 1.5.
* >FROZEN removed when hit with a FIRE attack.
* >FROZEN removed when hit with an EARTH attack.
* 
* CONDUCTIVE:
* >Applied when hit with an ELECTRICTY attack.
* >When hit with another ELECTRICTY attack, will send a shock attack to a nearby enemy.
* >CONDUCTIVE removed when hit with a WATER attack. Replaced with STUNNED instead.
* 
* STUNNED:
* >Applied when hit with ELECTRICTY and WATER attacks. (See WET and CONDUCTIVE)
* >Character can not moved while STUNNED.
*/