#ifndef WOBBLEMATERIAL_HPP
#define WOBBLEMATERIAL_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"

class ShaderProgram;
class Texture;

class WobbleMaterial : public AbstractMaterial
{
public:
	WobbleMaterial(Texture* diffuseTexture);
	virtual ~WobbleMaterial();
	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;
	void SetDiffuseTexture(Texture* diffuseTexture);

private:
	static ShaderProgram* shader;
	static void lazyInitializeShader();

	static GLint uMVPMatrix;
	static GLint uDiffuseTexture;
	static GLint uTime;

	static GLint aVertex;
	static GLint aNormal;
	static GLint aUV;

	Texture* diffuseTexture;

	WobbleMaterial(const WobbleMaterial&);
	WobbleMaterial& operator=(const WobbleMaterial&);
};

#endif