#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"

Light::Light(const std::string& pName, 
	const glm::vec3& pPosition,
	LightType lightType,
	glm::vec3 ambientColour,
	glm::vec3 diffuseColour,
	float intensity) :
	GameObject(pName, pPosition), 
	lightType(lightType),
	ambientColour(ambientColour),
	diffuseColour(diffuseColour),
	intensity(intensity)
{
	GameObject* directionCube = new GameObject("directionCube", glm::vec3(0, 0, 2));
	directionCube->scale(glm::vec3(0.15f, 0.15f, 0.15f));
	directionCube->setMesh(Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj"));
	directionCube->setMaterial(new ColorMaterial(glm::vec3(0, 1, 0.9903f)));
	_world->add(directionCube);
	add(directionCube);
}

Light::~Light() {
}

//Override setWorldRecursively to make sure we are registered
//to the world we are a part of.
void Light::_setWorldRecursively (World* pWorld) {

    //store the previous and new world before and after storing the given world
    World* previousWorld = _world;
    GameObject::_setWorldRecursively(pWorld);
    World* newWorld = _world;

    //check whether we need to register or unregister
    if (previousWorld != nullptr) previousWorld->unregisterLight(this);
	if (newWorld != nullptr) newWorld->registerLight(this);

}

void Light::SetLightType(LightType lightType)
{
	this->lightType = lightType;
}

LightType Light::GetLightType()
{
	return lightType;
}

void Light::SetAmbientColour(glm::vec3 colour)
{
	this->ambientColour = colour;
}

glm::vec3 Light::GetAmbientColour()
{
	return ambientColour;
}

void Light::SetDiffuseColour(glm::vec3 colour)
{
	this->diffuseColour = colour;
}

glm::vec3 Light::GetDiffuseColour()
{
	return diffuseColour;
}

void Light::SetIntensity(float value)
{
	this->intensity = value;
}

float Light::GetIntensity()
{
	return intensity;
}

glm::vec3 Light::GetForward()
{
	return -(getChildAt(0)->getWorldPosition() - getWorldPosition());
}
