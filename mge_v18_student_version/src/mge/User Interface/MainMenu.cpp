#include "MainMenu.hpp"

MainMenu::MainMenu(World* world, sf::Window* window) : world(world)
{
	startButton = new Button("mge\\UI\\Start_Button.png");
	startButton->SetCommand(new StartCommand());
	startButton->SetPosition(glm::vec2(300, 200));
	ButtonManager::AddButton(startButton);
	
	//Mouse setup
	mouse = new GameObject("Mouse");
	mouseBehaviour = new MouseBehaviour(window);
	mouse->setBehaviour(mouseBehaviour);
	world->add(mouse);
}

MainMenu::~MainMenu()
{
	std::cout << "GC running on:MainMenu.\n";
	delete mouseBehaviour;
	
	world->remove(mouse);
	delete mouse;
	ButtonManager::RemoveButton(startButton);
	std::cout << "Amount of Buttons: " << ButtonManager::GetAmountOfButtons() << std::endl;
}

