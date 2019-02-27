#pragma once
#include "SFML/Graphics.hpp"
#include "glm.hpp"
#include "mge/gameplay/Command/Command.hpp"
class Button
{
public:
	Button(const std::string& texturePath);
	~Button();
	void SetPosition(glm::vec2 position);
	glm::vec2 GetPosition();
	glm::vec2 GetSize();
	Command* GetButtonAction();
	void SetCommand(Command* command);

private:
	sf::Sprite* buttonImage;
	sf::Texture buttonTexture;
	Command* action;
};