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
	Normal = true;
}

void Status::setBurning()
{
	if (isWet)
	{
		setNormal();
		return;
	}
	if (isChilled)
	{
		setNormal();
		return;
	}
	if (isFrozen)
	{
		freezeDuration = 0.0;
		setNormal();
		return;
	}
	if (isConductive)
	{
		Conductive = false;
	}
	if (isBurning)
	{
		duration += 2.0;
	}
	else
	{
		Burning = true;
		duration = 5.0;
		DOT = 0.5;
	}
}

void Status::setWet()
{
	if (isBurning)
	{
		setNormal();
		return;
	}
	if (isChilled)
	{
		Chilled = false;
		setFrozen();
		return;
	}
	if (isFrozen)
	{
		duration += 1.0;
		return;
	}
	if (isConductive)
	{
		Conductive = false;
		setStunned();
		return;
	}
	if (isStunned)
	{
		return;
	}
	if (isWet)
	{
		duration += 2.0;
	}
	else
	{
		Wet = true;
		duration = 10;
		DOT = 0.0;
	}
}

void Status::setChilled()
{
	if (isBurning)
	{
		setNormal();
		return;
	}
	if (isWet)
	{
		Wet = false;
		setFrozen();
		return;
	}
	if (isFrozen)
	{
		duration += 2.0;
	}
	if (isConductive)
	{
		Conductive = false;
	}
	if (isChilled)
	{
		duration += 1.0;
	}
	else
	{
		Chilled = true;
		duration = 10;
		DOT = 0.0;
	}
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

float Status::getFreezeDuration()
{
	return freezeDuration;
}

void Status::setFreezeDuration(float amt)
{
	freezeDuration = amt;
}

float Status::getDOT()
{
	return DOT;
}

bool Status::isNormal()
{
	return Normal;
}

bool Status::isBurning()
{
	return Burning;
}

bool Status::isWet()
{
	return Wet;
}

bool Status::isChilled()
{
	return Chilled;
}

bool Status::isFrozen()
{
	return Frozen;
}

bool Status::isConductive()
{
	return Conductive;
}

bool Status::isStunned()
{
	return Stunned;
}