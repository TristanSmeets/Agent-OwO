#ifndef TESTFACTORY_HPP
#define TESTFACTORY_HPP

#include "mge/core/AbstractFactory.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/core/Mesh.hpp"

class TestFactory : public AbstractFactory
{
public:
	TestFactory();
	virtual ~TestFactory();
	GameObject* CreateGameObject(const std::string& name);

private:
	void addMesh(GameObject* gameObject);
	void addMaterial(GameObject* gameObject);
	void addBehaviour(GameObject* gameObject);
	ColorMaterial* colourMaterial;
	Mesh* cubeMesh;
	TextureMaterial* textureMaterial;
};

#endif // !TESTFACTORY_HPP
