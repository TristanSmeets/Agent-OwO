#ifndef TESTFACTORY_HPP
#define TESTFACTORY_HPP

#include "mge/core/AbstractFactory.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/core/Mesh.hpp"

class TestFactory : public AbstractFactory
{
public:
	TestFactory();
	virtual ~TestFactory();
	GameObject* CreateGameObject(const std::string& objectType);

private:
	ColorMaterial* colourMaterial;
	Mesh* cubeMesh;
};

#endif // !TESTFACTORY_HPP
