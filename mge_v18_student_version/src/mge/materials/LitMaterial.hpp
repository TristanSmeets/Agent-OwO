#ifndef LITMATERIAL_HPP
#define LITMATERIAL_HPP

#include "GL/glew.h"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Texture.hpp"

class ShaderProgram;
class Texture;

class LitMaterial : public AbstractMaterial
{
public:
	LitMaterial(Texture* pDiffuseTexture, glm::vec3 pColour= glm::vec3(1,0,0));
	virtual ~LitMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	//in rgb values
	void SetDiffuseColour(glm::vec3 diffuseColour);

private:

	static ShaderProgram* shader;
	
	static void lazyInitializeShader();
	Texture* diffuseTexture;

	glm::vec3 ambientColour;
};

#endif
