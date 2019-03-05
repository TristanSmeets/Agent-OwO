#pragma once

struct SwitchEvent
{
	int activateSwitch = 0;
};

struct GeneralEvent
{
	int stepsTaken = 0;
	bool resetLevel = false;
	bool nextLevel = false;
	bool startGame = false;
	bool showStartDialogue = false;
	bool showEndDialogue = false;
	bool nextDialogue = false;
	bool isDialogueCompleted = false;
};