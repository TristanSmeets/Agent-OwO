#include "glm.hpp"

#include "LitMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Light.hpp"

ShaderProgram* LitMaterial::shader = NULL;

LitMaterial::LitMaterial()
{
	lazyInitializeShader();
}

LitMaterial::~LitMaterial()
{
}

void LitMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	shader->use();
	
	if (pWorld->getLightCount() > 0)
	{
		for (int index = 0; index < pWorld->getLightCount(); index++)
		{
			Light* light = pWorld->getLightAt(index);
			if (light->GetLightType() == LightType::POINT)
			{
				//Set Light position
				glUniform3fv(shader->getUniformLocation("lightPosition"), 1, glm::value_ptr(light->getWorldPosition()));
			}
			else if (light->GetLightType() == LightType::DIRECTIONAL)
			{
				//Get lights forward vector.
				//TODO: Vragen hoe de forward vector te krijgen.
				glm::mat4 lightTransform = light->getWorldTransform();
				glm::vec3 LightPosition = light->getWorldPosition();
				glm::vec3 lightForward = LightPosition;

				std::cout << "Z-Component: " << lightForward << std::endl;
				glUniform3fv(shader->getUniformLocation("lightPosition"), 1, glm::value_ptr(lightForward));
			}
			//Set ambientColour
			glUniform3fv(shader->getUniformLocation("ambientColour"), 1, glm::value_ptr(light->GetAmbientColour()));

			//Set diffuseColour
			glUniform3fv(shader->getUniformLocation("lightColour"), 1, glm::value_ptr(light->GetDiffuseColour()));

			//Set intensity
			glUniform1f(shader->getUniformLocation("ambientStrength"), light->GetIntensity());
		}
	}

	//pass in all MVP matrices separately
	glUniformMatrix4fv(shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(
		shader->getAttribLocation("vertex"),
		shader->getAttribLocation("normal"),
		shader->getAttribLocation("uv")
	);
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
