#include "MainMenu.hpp"

MainMenu::MainMenu(World* world, sf::Window* window) : world(world)
{
	//Start Button
	startButton = new Button("mge\\UI\\Start_Button.png");
	startButton->SetCommand(new StartCommand());
	startButton->SetPosition(glm::vec2(400, 200));
	ButtonManager::AddButton(startButton);

	//Exit Button
	exitButton = new Button("mge\\UI\\Exit_Button.png");
	exitButton->SetCommand(new ExitCommand(window));
	exitButton->SetPosition(glm::vec2(400, 400));
	ButtonManager::AddButton(exitButton);

	//Mouse setup
	mouse = new GameObject("Mouse");
	mouseBehaviour = new MouseBehaviour(window);
	mouse->setBehaviour(mouseBehaviour);
	world->add(mouse);

	backgroundTexture = new sf::Texture();
	backgroundTexture->loadFromFile("mge\\UI\\BG_MainMenu.png");
	BackgroundImage.setTexture(*backgroundTexture);
}

MainMenu::~MainMenu()
{
	std::cout << "GC running on:MainMenu.\n";
	delete mouseBehaviour;

	world->remove(mouse);
	delete mouse;
	ButtonManager::RemoveButton(startButton);
	ButtonManager::RemoveButton(exitButton);

	delete backgroundTexture;
	std::cout << "Amount of Buttons: " << ButtonManager::GetAmountOfButtons() << std::endl;
}

void MainMenu::Draw(sf::RenderWindow* window)
{
	window->draw(BackgroundImage);
	if (ButtonManager::GetAmountOfButtons() > 0)
	{
		for (unsigned int index = 0; index < ButtonManager::GetAmountOfButtons(); ++index)
		{
			Button* current = ButtonManager::GetButton(index);
			window->draw(*current->GetSprite());
		}
	}
}

