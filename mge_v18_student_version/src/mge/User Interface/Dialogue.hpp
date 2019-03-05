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
	void Draw(sf::RenderWindow* window);

private:
	void loadStartDialogue(int level);
	void loadEndDialogue(int level);
	void setCurrentImage(int imageIndex);

	lua_State* luaDialogue;
	int levelNumber = 0;
	int amountOfLevels = 0;
	int currentImage = 0;
	sf::Texture* currentTexture;
	DIALOGUE dialogueType = DIALOGUE::START_DIALOGUE;
	std::vector<sf::Image> startDialogue;
	std::vector<sf::Image> endDialogue;
	sf::Sprite currentDialogue;
};