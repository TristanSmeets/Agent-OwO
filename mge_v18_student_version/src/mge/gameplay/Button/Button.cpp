#include "Button.hpp"

Button::Button(const std::string & texturePath)
{
	std::cout << "Creating buttonTexture.\n";
	buttonTexture.loadFromFile(texturePath);
	buttonImage = new sf::Sprite(buttonTexture);
}

Button::~Button()
{
	std::cout << "GC running:Button.\n";
	delete buttonImage;
	delete action;
}

void Button::SetPosition(glm::vec2 position)
{
	buttonImage->setPosition(position.x, position.y);
}

glm::vec2 Button::GetPosition()
{
	sf::Vector2f imagePosition = buttonImage->getPosition();

	return glm::vec2(imagePosition.x,imagePosition.y);
}

glm::vec2 Button::GetSize()
{
	sf::Vector2u imageSize = buttonImage->getTexture()->getSize();
	return glm::vec2(imageSize.x,imageSize.y);
}

Command * Button::GetButtonAction()
{
	return action;
}

void Button::SetCommand(Command * command)
{
	action = command;
}
