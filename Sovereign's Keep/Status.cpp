#include "Status.h"

void Status::setNormal()
{
	statusDuration = 0.0f;
	DOT = 0.0f;
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
		if (statusDuration < burningDuration * 3)
		{
			statusDuration += 2.0f;
		}
	}
	else
	{
		Burning = true;
		Normal = false;
		statusDuration = burningDuration;
		DOT = 0.5f;
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
		if (statusDuration < wetDuration * 3)
		{
			statusDuration += 2.0f;
		}
	}
	else
	{
		Wet = true;
		Normal = false;
		statusDuration = wetDuration;
		DOT = 0.0f;
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
		statusDuration += 2.0f;
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
		if (statusDuration < chilledDuration * 3)
		{
			statusDuration += 2.0f;
		}
	}
	else
	{
		Chilled = true;
		Normal = false;
		statusDuration = chilledDuration;
		DOT = 0.0f;
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
		if (statusDuration < frozenDuration * 3)
		{
			statusDuration += 2.0f;
		}
	}
	else
	{
		Frozen = true;
		Normal = false;
		statusDuration = frozenDuration;
		DOT = 0.0f;
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
		Wet = false;
		setStunned();
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
		if (statusDuration < conductiveDuration * 3)
		{
			statusDuration += 2.0f;
		}
	}
	else
	{
		Conductive = true;
		Normal = false;
		statusDuration = conductiveDuration;
		DOT = 0.0f;
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
		if (statusDuration < stunnedDuration * 3)
		{
			statusDuration += 2.0f;
		}
	}
	else
	{
		Stunned = true;
		Normal = false;
		statusDuration = stunnedDuration;
		DOT = 0.0f;
	}
}