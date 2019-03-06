#include "DeathScreen.hpp"

DeathScreen::DeathScreen(World* world, sf::Window* window) : world(world)
{
	//Retry Button
	retryButton = new Button("mge\\UI\\Retry_Button.png");
	retryButton->SetCommand(new RetryCommand());
	retryButton->SetPosition(glm::vec2(400, 200));
	ButtonManager::AddButton(retryButton);

	//Quit Button
	quitButton = new Button("mge\\UI\\Quit_Button.png");
	quitButton->SetCommand(new QuitCommand());
	quitButton->SetPosition(glm::vec2(400, 400));
	ButtonManager::AddButton(quitButton);

	//Background filter
	backgroundTexture = new sf::Texture();
	backgroundTexture->loadFromFile("mge\\UI\\black_filter.png");
	backgroundImage.setTexture(*backgroundTexture);

	//Mouse setup
	mouse = new GameObject("MOUSE");
	mouseBehaviour = new MouseBehaviour(window);
	mouse->setBehaviour(mouseBehaviour);
	world->add(mouse);
}

DeathScreen::~DeathScreen()
{
	std::cout << "GC running on:MainMenu.\n";
	delete mouseBehaviour;

	world->remove(mouse);
	delete mouse;
	ButtonManager::RemoveButton(retryButton);
	ButtonManager::RemoveButton(quitButton);

	delete backgroundTexture;
}

void DeathScreen::Draw(sf::RenderWindow * window)
{
	window->draw(backgroundImage);
	if (ButtonManager::GetAmountOfButtons() > 0)
	{
		for (unsigned int index = 0; index < ButtonManager::GetAmountOfButtons(); ++index)
		{
			Button* current = ButtonManager::GetButton(index);
			window->draw(*current->GetSprite());
		}
	}
}
