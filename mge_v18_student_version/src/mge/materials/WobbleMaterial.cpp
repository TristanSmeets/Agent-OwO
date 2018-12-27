#include "WobbleMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

ShaderProgram* WobbleMaterial::shader = NULL;

GLint WobbleMaterial::uMVPMatrix = 0;
GLint WobbleMaterial::uDiffuseTexture = 0;

GLint WobbleMaterial::aVertex = 0;
GLint WobbleMaterial::aNormal = 0;
GLint WobbleMaterial::aUV = 0;

WobbleMaterial::WobbleMaterial(Texture * diffuseTexture): diffuseTexture(diffuseTexture)
{
	lazyInitializeShader();
}

WobbleMaterial::~WobbleMaterial()
{
}

void WobbleMaterial::render(World * pWorld, Mesh * pMesh, const glm::mat4 & pModelMatrix, const glm::mat4 & pViewMatrix, const glm::mat4 & pProjectionMatrix)
{
	if (!diffuseTexture) return;

	shader->use();

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, diffuseTexture->getId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(uDiffuseTexture, 0);

	//pass in a precalculate mvp matrix (see texture material for the opposite)
	glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
	glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(aVertex, aNormal, aUV);
}

void WobbleMaterial::SetDiffuseTexture(Texture * diffuseTexture)
{
	this->diffuseTexture = diffuseTexture;
}

void WobbleMaterial::lazyInitializeShader()
{
	if (!shader)
	{
		shader = new ShaderProgram();
		shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "");
		shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "");
		shader->finalize();

		uMVPMatrix = shader->getUniformLocation("mvpMatrix");
		uDiffuseTexture = shader->getUniformLocation("diffuseTexture");

		aVertex = shader->getAttribLocation("vertex");
		aNormal = shader->getAttribLocation("normal");
		aUV = shader->getAttribLocation("uv");
	}
}
