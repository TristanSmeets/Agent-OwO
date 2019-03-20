#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"

Light::Light(const std::string& pName, 
	const glm::vec3& pPosition, LightingData* data) :
	GameObject(pName, pPosition), 
	data(data)
{
	GameObject* directionCube = new GameObject("directionCube", glm::vec3(0, 0, 2));
	directionCube->scale(glm::vec3(0.15f, 0.15f, 0.15f));
	directionCube->setMesh(Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj"));
	directionCube->setMaterial(new ColorMaterial(glm::vec3(0, 1, 0.9903f)));
	_world->add(directionCube);
	add(directionCube);
}

Light::~Light() 
{
	delete data;
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
	data->Type = lightType;
}

LightType Light::GetLightType()
{
	return data->Type;
}

void Light::SetAmbientColour(glm::vec3 colour)
{
	data->Ambient = colour;
}

glm::vec3 Light::GetAmbientColour()
{
	return data->Ambient;
}

void Light::SetDiffuseColour(glm::vec3 colour)
{
	data->Diffuse = colour;
}

glm::vec3 Light::GetDiffuseColour()
{
	return data->Diffuse;
}

void Light::SetSpecularColour(glm::vec3 colour)
{
	data->Specular = colour;
}

glm::vec3 Light::GetSpecularColour()
{
	return data->Specular;;
}

void Light::SetLightConstant(float value)
{
	data->Constant = value;
}

float Light::GetLightConstant()
{
	return data->Constant;
}

void Light::SetLightLinear(float value)
{
	data->Linear = value;
}

float Light::GetLightLinear()
{
	return data->Linear;
}

void Light::SetLightQuadratic(float value)
{
	data->Quadratic = value;
}

float Light::GetLightQuadratic()
{
	return data->Quadratic;
}

void Light::SetLightCutOff(float value)
{
	data->CutOff = value;
}

float Light::GetLightCutOff()
{
	return glm::cos(glm::radians(data->CutOff));
}

void Light::SetLightOuterCutOff(float value)
{
	data->OuterCutOff = value;
}

float Light::GetLightOuterCutOff()
{
	return glm::cos(glm::radians(data->OuterCutOff));
}

glm::vec3 Light::GetForward()
{
	return getWorldTransform()[2];
}
