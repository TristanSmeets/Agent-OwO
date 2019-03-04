#pragma once
#include "mge/util/EventQueue/EventQueue.hpp"
#include "mge/core/Observer.hpp"
#include "mge/core/Subject.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

enum DIALOGUE{ START_DIALOGUE, END_DIALOGUE };

class Dialogue: public Observer<GeneralEvent>
{
public:
	Dialogue();
	~Dialogue();
	void OnNotify(const GeneralEvent& info);
	void LoadDialogues(int level);

private:
	void loadStartDialogue(int level);
	void loadEndDialogue(int level);
	void setCurrentImage(int imageIndex);
	void unloadDialogues();

	lua_State* luaDialogue;
	int levelNumber = 0;
	int amountOfLevels = 0;
	int currentImage = 0;
	DIALOGUE dialogueType;
	std::vector<sf::Texture> startDialogue;
	std::vector<sf::Texture> endDialogue;
	sf::Sprite currentDialogue;
};