#include "CameraFactory.hpp"
#include "mge/core/Camera.hpp"
#include <iostream>

CameraFactory::CameraFactory(lua_State* config) : AbstractFactory(), config(config)
{
	material = nullptr;
	mesh = nullptr;
	behaviour = nullptr;
}

CameraFactory::~CameraFactory()
{
	std::cout << "GC running on:CameraFactory\n";
	config = nullptr;
}

GameObject* CameraFactory::CreateGameObject(const std::string & name)
{
	float orthoVertical = LuaWrapper::GetNumber<float>(config, "OrthoVertical");
	float orthoHorziontal = LuaWrapper::GetNumber<float>(config, "OrthoHorizontal");
	return new Camera(name,
		glm::vec3(0, 0, 0),
		glm::ortho(-orthoHorziontal, orthoHorziontal, -orthoVertical, orthoVertical, 0.1f, 100.0f));
}

