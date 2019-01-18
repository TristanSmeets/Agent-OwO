#ifndef LITMATERIAL_HPP
#define LITMATERIAL_HPP

#include "GL/glew.h"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "glm.hpp"

class ShaderProgram;

struct SpecularData {
	glm::vec3 Colour;
	int ShininessFactor;
	float Strength;
};

class LitMaterial : public AbstractMaterial
{
public:
	LitMaterial(SpecularData* specularData);
	virtual ~LitMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

private:
	static ShaderProgram* shader;
	static void lazyInitializeShader();
	SpecularData* specularData;
};

#endif
