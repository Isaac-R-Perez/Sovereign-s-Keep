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
	if (Wet)
	{
		setNormal();
		return;
	}
	if (Chilled)
	{
		setNormal();
		return;
	}
	if (Frozen)
	{
		setNormal();
		return;
	}
	if (Conductive)
	{
		setNormal();
	}
	if (Stunned)
	{
		return;
	}
	if (Burning)
	{
		duration += 2.0;
	}
	else
	{
		Burning = true;
		Normal = false;
		duration = 5.0;
		DOT = 0.5;
	}
}

void Status::setWet()
{
	if (Burning)
	{
		setNormal();
		return;
	}
	if (Chilled)
	{
		Chilled = false;
		setFrozen();
		return;
	}
	if (Frozen)
	{
		return;
	}
	if (Conductive)
	{
		Conductive = false;
		setStunned();
		return;
	}
	if (Stunned)
	{
		return;
	}
	if (Wet)
	{
		duration += 2.0;
	}
	else
	{
		Wet = true;
		Normal = false;
		duration = 7.0;
		DOT = 0.0;
	}
}

void Status::setChilled()
{
	if (Burning)
	{
		setNormal();
		return;
	}
	if (Wet)
	{
		Wet = false;
		setFrozen();
		return;
	}
	if (Frozen)
	{
		duration += 2.0;
		return;
	}
	if (Conductive)
	{
		Conductive = false;
	}
	if (Stunned)
	{
		return;
	}
	if (Chilled)
	{
		Chilled = true;
		duration += 2.0;
	}
	else
	{
		Chilled = true;
		Normal = false;
		duration = 5.0;
		DOT = 0.0;
	}
}

void Status::setFrozen()
{
	if (Burning)
	{
		Burning = false;
	}
	if (Wet)
	{
		Wet = false;
	}
	if (Chilled)
	{
		Chilled = false;
	}
	if (Conductive)
	{
		Conductive = false;
	}
	if (Stunned)
	{
		Stunned = false;
	}
	if (Frozen)
	{
		duration += 2.0;
	}
	else
	{
		Frozen = true;
		Normal = false;
		duration = 5.0;
		DOT = 0.0;
	}
}

void Status::setConductive()
{
	if (Burning)
	{
		setNormal();
		return;
	}
	if (Wet)
	{
		setNormal();
		return;
	}
	if (Chilled)
	{
		setNormal();
		return;
	}
	if (Frozen)
	{
		return;
	}
	if (Stunned)
	{
		return;
	}
	if (Conductive)
	{
		duration += 2.0;
	}
	else
	{
		Conductive = true;
		Normal = false;
		duration = 7.0;
		DOT = 0.0;
	}
}

void Status::setStunned()
{
	if (Burning)
	{
		Burning = false;
	}
	if (Wet)
	{
		Wet = false;
	}
	if (Chilled)
	{
		Chilled = false;
	}
	if (Frozen)
	{
		Frozen = false;
	}
	if (Conductive)
	{
		Conductive = false;
	}
	if (Stunned)
	{
		duration += 2.0;
	}
	else
	{
		Stunned = true;
		Normal = false;
		duration = 5.0;
		DOT = 0.0;
	}
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