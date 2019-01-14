#include "glm.hpp"

#include "LitMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"

ShaderProgram* LitMaterial::shader = NULL;

LitMaterial::LitMaterial(SpecularData* specularData) : specularData(specularData)
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
				glm::vec4 PositionVector = glm::vec4(light->getWorldPosition(), 1.0f);
				glUniform4fv(shader->getUniformLocation("light.position"), 1, glm::value_ptr(PositionVector));
			}
			else if (light->GetLightType() == LightType::DIRECTIONAL)
			{
				//Get lights forward vector.
				glm::vec4 DirectionVector = glm::vec4(light->GetForward(), 0.0f);
				glUniform4fv(shader->getUniformLocation("light.position"), 1, glm::value_ptr(DirectionVector));
			}
			//Set ambientColour
			glUniform3fv(shader->getUniformLocation("light.ambient"), 1, glm::value_ptr(light->GetAmbientColour()));

			//Set diffuseColour
			glUniform3fv(shader->getUniformLocation("light.diffuse"), 1, glm::value_ptr(light->GetDiffuseColour()));

			//Set specularColour
			glUniform3fv(shader->getUniformLocation("light.specular"), 1, glm::value_ptr(specularData->Colour));

			//Set intensity
			glUniform1f(shader->getUniformLocation("light.ambientStrength"), light->GetAmbientStrength());

			//Set SpecularStrength
			glUniform1f(shader->getUniformLocation("light.specularStrength"), specularData->Strength);
			
			//Set shininess highlight
			glUniform1i(shader->getUniformLocation("light.shininessFactor"), specularData->ShininessFactor);

			//Set LightConstant
			glUniform1f(shader->getUniformLocation("light.constant"), light->GetLightConstant());

			//Set LightLinear
			glUniform1f(shader->getUniformLocation("light.linear"), light->GetLightLinear());

			//Set LightQuadratic
			glUniform1f(shader->getUniformLocation("light.quadratic"), light->GetLightQuadratic());
		}
		
		//Set Object Colour;
		glUniform3fv(shader->getUniformLocation("objectColour"), 1, glm::value_ptr(glm::vec3(1, 1, 1)));
		
		//Set view position
		Camera* camera = pWorld->getMainCamera();
		glm::vec3 cameraPos = camera->getWorldPosition();
		glUniform3fv(shader->getUniformLocation("viewPos"), 1, glm::value_ptr(cameraPos));
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
