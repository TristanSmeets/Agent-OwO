#include "UIStepCounter.hpp"

UIStepCounter::UIStepCounter(lua_State* luaHUD, int levelNumber) : Observer<GeneralEvent>()
{
	std::cout << "Creating UI StepCounter.\n";
	EventQueue::AddObserver(this);
	//Getting amount of steps
	lua_State* luaLevelInfo = LuaWrapper::InitializeLuaState("LuaGameScripts/Level/Level_Info.lua");
	lua_getglobal(luaLevelInfo, "AmountOfSteps");
	std::cout << "Getting totalSteps.\n";
	totalSteps = LuaWrapper::GetTableNumber(luaLevelInfo, "Level_" + std::to_string(levelNumber));
	stepsLeft = totalSteps;

	//Creating Icon
	iconImage = sf::Sprite();
	//std::cout << "Trying to get IconPath.\n";
	//std::string iconPath = LuaWrapper::GetString(luaHUD, "IconPath");

	//std::cout << "IconPath: " << iconPath << std::endl;
	iconTexture.loadFromFile("mge/UI/Footsteps.png");
	iconImage.setTexture(iconTexture);
	//glm::vec2 iconPosition = LuaWrapper::GetVec2(luaHUD, "IconPosition");
	//iconImage.setPosition(iconPosition.x, iconPosition.y);
	iconImage.setPosition(200, 500);
	sf::Vector2u iconSize = iconImage.getTexture()->getSize();
	iconImage.setOrigin(iconSize.x * 0.5f, iconSize.y * 0.5f);

	//Creating font
	std::string fontPath = "mge/UI/Futura_ICG.ttf";//LuaWrapper::GetString(luaHUD, "Font");
	font.loadFromFile(fontPath);
	

	//Creating Text
	stepText = sf::Text();
	stepText.setFont(font);
	stepText.setCharacterSize(16);//LuaWrapper::GetNumber<int>(luaHUD, "FontSize"));
	//glm::vec2 textPosition = LuaWrapper::GetVec2(luaHUD, "TextPosition");
	//stepText.setPosition(textPosition.x, textPosition.y);
	stepText.setPosition(200, 600);
	updateStepCounter(stepsLeft);
}

UIStepCounter::~UIStepCounter()
{
	std::cout << "GC running on:UIStepCounter.\n";
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

void UIStepCounter::resetStepCounter()
{
	stepsLeft = totalSteps;
	updateStepCounter(stepsLeft);
}

void UIStepCounter::updateStepCounter(int Number)
{
	stepText.setString(std::to_string(Number));
}
