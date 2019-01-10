#include "glm.hpp"

#include "LitMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"

ShaderProgram* LitMaterial::shader = NULL;

LitMaterial::LitMaterial(Texture* pDiffuseTexture, glm::vec3 pColour): diffuseTexture(pDiffuseTexture), ambientColour(pColour)
{
	lazyInitializeShader();
}

LitMaterial::~LitMaterial()
{
}

void LitMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	shader->use();

	//set the material color
	glUniform3fv(shader->getUniformLocation("ambientColour"), 1, glm::value_ptr(ambientColour));

	//pass in all MVP matrices separately
	glUniformMatrix4fv(shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));
	
	//Setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//Bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, diffuseTexture->getId());
	//Tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(shader->getUniformLocation("diffuseTexture"), 0);

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(
		shader->getAttribLocation("vertex"),
		shader->getAttribLocation("normal"),
		shader->getAttribLocation("uv")
	);
}

void LitMaterial::SetDiffuseColour(glm::vec3 pDiffuseColour)
{
	ambientColour = pDiffuseColour;
}

void LitMaterial::lazyInitializeShader()
{
	if (!shader)
	{
		shader = new ShaderProgram();
		shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "lit.vs");
		shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "lit.fs");
		shader->finalize();
	}
}
