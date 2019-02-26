#pragma once

struct SwitchEvent
{
	int activateSwitch = 0;
};

struct GeneralEvent
{
	int stepsTaken = 0;
	bool resetLevel = false;
	int nextLevel = 0;
};
