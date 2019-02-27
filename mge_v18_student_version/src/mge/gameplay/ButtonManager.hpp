#pragma once
#include <vector>
#include <algorithm>
#include "mge/gameplay/Button/Button.hpp"

class ButtonManager
{
public:
	ButtonManager();
	~ButtonManager();
	static void AddButton(Button* button);
	static void RemoveButton(Button* button);
	static Button* GetButton(int index);
	static int GetAmountOfButtons();

private:
	static std::vector<Button*> buttons;
};
