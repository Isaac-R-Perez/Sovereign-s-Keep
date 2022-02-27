#include "Status.h"

void Status::setNormal()
{
	duration = 0.0;
	DOT = 0.0;
	Burning = false;
	Wet = false;
	Chilled = false;
	Frozen = false;
	Conductive = false;
	Stunned = false;
}

void Status::setBurning()
{
	duration = 5.0;
	DOT = 0.5;
	Burning = true;
}

void Status::setWet()
{
	duration = 10;
	DOT = 0.0;
	Wet = true;
}

void Status::setChilled()
{
	duration = 10;
	DOT = 0.0;
	Chilled = true;
}

void Status::setFrozen()
{
	duration = 5;
	DOT = 0.0;
	Wet = false;
	Chilled = false;
	Frozen = true;
}

void Status::setConductive()
{
	duration = 10;
	DOT = 0.0;
	Conductive = true;
}

void Status::setStunned()
{
	duration = 5;
	DOT = 0.1;
	Wet = false;
	Conductive = false;
	Stunned = true;
}

//GETTERS and SETTERS
float Status::getDuration()
{
	return duration;
}

void Status::setDuration(float amt)
{
	duration = amt;
}

float Status::getDOT()
{
	return DOT;
}

bool Status::isBurning()
{
	return isBurning;
}

bool Status::isWet()
{
	return isWet;
}

bool Status::isChilled()
{
	return isChilled;
}

bool Status::isFrozen()
{
	return isFrozen;
}

bool Status::isConductive()
{
	return isConductive;
}

bool Status::isStunned()
{
	return isStunned;
}