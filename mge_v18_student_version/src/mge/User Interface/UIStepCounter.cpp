#include "UIStepCounter.hpp"

UIStepCounter::UIStepCounter(int levelNumber) : Observer<GeneralEvent>()
{
	EventQueue::AddObserver(this);
	//Getting amount of steps
	lua_State* luaLevelInfo = LuaWrapper::InitializeLuaState("LuaGameScripts/Level/Level_Info.lua");
	lua_getglobal(luaLevelInfo, "AmountOfSteps");
	totalSteps = LuaWrapper::GetTableNumber(luaLevelInfo, "Level_" + std::to_string(levelNumber));
	stepsLeft = totalSteps;
	initialize();
	LuaWrapper::CloseLuaState(luaLevelInfo);
}

UIStepCounter::~UIStepCounter()
{
	EventQueue::RemoveObserver(this);
}

void UIStepCounter::OnNotify(const GeneralEvent & info)
{
	if (info.stepsTaken > 0)
	{
		stepsLeft -= info.stepsTaken;
		updateStepCounter(stepsLeft);
	}
	if (info.resetLevel)
		resetStepCounter();
}

void UIStepCounter::Draw(sf::RenderWindow * window)
{
	window->draw(stepText);
	window->draw(iconImage);
}

void UIStepCounter::initialize()
{
	lua_State* luaHUD = LuaWrapper::InitializeLuaState("LuaGameScripts\\UI\\HUD.lua");
	lua_getglobal(luaHUD, "Buttons");

	lua_pushnil(luaHUD);

	while (lua_next(luaHUD, -2) != 0)
	{
		glm::vec3 position = LuaWrapper::GetTableVec3(luaHUD, "Position");
		std::string UIType = LuaWrapper::GetTableString(luaHUD, "Type");

		if (UIType == "IMAGE")
		{
			std::string imagePath = LuaWrapper::GetTableString(luaHUD, "ImagePath");
			iconTexture.loadFromFile(imagePath);
			iconImage.setTexture(iconTexture);
			iconImage.setPosition(sf::Vector2f(position.x, position.y));
			sf::Vector2u imageSize = iconTexture.getSize();
			iconImage.setOrigin(imageSize.x * .5f, imageSize.y * .5f);
		}

		if (UIType == "TEXT")
		{
			std::cout << "Creating text.\n";
			std::string fontPath = LuaWrapper::GetTableString(luaHUD, "FontPath");
			int fontSize = LuaWrapper::GetTableNumber(luaHUD, "FontSize");
			font.loadFromFile(fontPath);
			stepText.setFont(font);
			stepText.setCharacterSize(fontSize);
			stepText.setPosition(sf::Vector2f(position.x, position.y));
			stepText.setFillColor(sf::Color(127, 252, 255));
			stepText.setOutlineColor(sf::Color(127, 252, 255));
			updateStepCounter(stepsLeft);
		}
		lua_pop(luaHUD, 1);
	}
	lua_pop(luaHUD, 1);

	LuaWrapper::CloseLuaState(luaHUD);
}

void UIStepCounter::resetStepCounter()
{
	stepsLeft = totalSteps;
	updateStepCounter(stepsLeft);
}

void UIStepCounter::updateStepCounter(int Number)
{
	stepText.setString(std::to_string(Number));
}
