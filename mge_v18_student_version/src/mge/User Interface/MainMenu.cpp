#include "MainMenu.hpp"

MainMenu::MainMenu(World* world, sf::Window* window) : world(world)
{
	//Start Button
	startButton = new Button("mge\\UI\\Start_Button.png");
	startButton->SetCommand(new StartCommand());
	startButton->SetPosition(glm::vec2(300, 200));
	ButtonManager::AddButton(startButton);
	
	//Exit Button
	exitButton = new Button("mge\\UI\\Exit_Button.png");
	exitButton->SetCommand(new ExitCommand(window));
	exitButton->SetPosition(glm::vec2(300, 400));
	ButtonManager::AddButton(exitButton);

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
	ButtonManager::RemoveButton(exitButton);
	std::cout << "Amount of Buttons: " << ButtonManager::GetAmountOfButtons() << std::endl;
}

