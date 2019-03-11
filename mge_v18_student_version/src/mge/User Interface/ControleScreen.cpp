#include "ControleScreen.hpp"

ControleScreen::ControleScreen(World * world, sf::RenderWindow * window) : world(world)
{
	initialize();

	mouse = new GameObject("MOUSE");
	mouseBehaviour = new MouseBehaviour(window);
	mouse->setBehaviour(mouseBehaviour);
	world->add(mouse);
}

ControleScreen::~ControleScreen()
{
	delete mouseBehaviour;
	world->remove(mouse);
	delete mouse;
	delete backgroundTexture;
	
	ButtonManager::RemoveButton(backButton);
	delete backButton;
}

void ControleScreen::Draw(sf::RenderWindow* window)
{
	window->draw(backgroundImage);

	if (ButtonManager::GetAmountOfButtons > 0)
	{
		for (unsigned int index = 0; index < ButtonManager::GetAmountOfButtons(); ++index)
		{
			Button* current = ButtonManager::GetButton(index);
			window->draw(*current->GetSprite());
		}
	}
}

void ControleScreen::initialize()
{
	lua_State* luaControls = LuaWrapper::InitializeLuaState("LuaGameScripts\\UI\\Controls.lua");
	lua_getglobal(luaControls, "Buttons");

	lua_pushnil(luaControls);

	while (lua_next(luaControls, -2) != 0)
	{
		glm::vec3 position = LuaWrapper::GetTableVec3(luaControls, "Position");
		std::string UIType = LuaWrapper::GetTableString(luaControls, "Type");
		std::string imagePath = LuaWrapper::GetTableString(luaControls, "ImagePath");

		if (UIType == "BUTTON")
		{
			std::string ButtonType = LuaWrapper::GetTableString(luaControls, "ButtonType");
			if (ButtonType == "RETURN")
			{
				backButton = new Button(imagePath);
				backButton->SetCommand(new QuitCommand());
				backButton->SetPosition(glm::vec2(position.x, position.y));
				ButtonManager::AddButton(backButton);
			}
		}

		if (UIType == "BACKGROUND")
		{
			backgroundTexture = new sf::Texture();
			backgroundTexture->loadFromFile(imagePath);
			backgroundImage.setTexture(*backgroundTexture);
			backgroundImage.setPosition(sf::Vector2f(position.x, position.y));
			sf::Vector2u bgSize = backgroundTexture->getSize();
			backgroundImage.setOrigin(bgSize.x * .5f, bgSize.y * .5f);
		}
		lua_pop(luaControls, 1);
	}
	lua_pop(luaControls, 1);

	LuaWrapper::CloseLuaState(luaControls);
}