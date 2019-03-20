#include "glm.hpp"

#include "LitMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"

ShaderProgram* LitMaterial::shader = NULL;
GLint LitMaterial::uDiffuseTexture = 0;
GLint LitMaterial::uSpecularTexture = 0;

LitMaterial::LitMaterial(Material* specularData) : material(specularData)
{
	lazyInitializeShader();
}

LitMaterial::~LitMaterial()
{
	delete shader;
	delete material;
}

void LitMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	shader->use();
	
	if (pWorld->getLightCount() > 0)
	{
		for (int index = 0; index < pWorld->getLightCount(); index++)
		{
			Light* light = pWorld->getLightAt(index);
			
			//Set light type

			switch (light->GetLightType())
			{
			case LightType::DIRECTIONAL:
				glUniform1i(shader->getUniformLocation("light.type"), 0);
				break;
			case LightType::POINT:
				glUniform1i(shader->getUniformLocation("light.type"), 1);
				break;
			case LightType::SPOTLIGHT:
				glUniform1i(shader->getUniformLocation("light.type"), 2);
				break;
			}

			//Set light position
			glUniform3fv(shader->getUniformLocation("light.position"), 1, glm::value_ptr(light->getWorldPosition()));

			//Set light direction
			glUniform3fv(shader->getUniformLocation("light.direction"), 1, glm::value_ptr(light->GetForward()));

			//Set light ambientColour
			glUniform3fv(shader->getUniformLocation("light.ambient"), 1, glm::value_ptr(light->GetAmbientColour()));

			//Set light diffuseColour
			glUniform3fv(shader->getUniformLocation("light.diffuse"), 1, glm::value_ptr(light->GetDiffuseColour()));
			
			//Set light specularColour
			glUniform3fv(shader->getUniformLocation("light.specular"), 1, glm::value_ptr(light->GetSpecularColour()));
			
			//Set LightConstant
			glUniform1f(shader->getUniformLocation("light.constant"), light->GetLightConstant());

			//Set LightLinear
			glUniform1f(shader->getUniformLocation("light.linear"), light->GetLightLinear());

			//Set LightQuadratic
			glUniform1f(shader->getUniformLocation("light.quadratic"), light->GetLightQuadratic());

			//Set Light CutOff
			glUniform1f(shader->getUniformLocation("light.cutOff"), light->GetLightCutOff());

			//Set Light OuterCutOff
			glUniform1f(shader->getUniformLocation("light.outerCutOff"), light->GetLightOuterCutOff());
		}
		
		//Setting material DiffuseTexture
		shader->setTextureSlot(material->DiffuseTexture, uDiffuseTexture, 0);
		//Setting material SpecularTexture
		shader->setTextureSlot(material->SpecularTexture, uSpecularTexture, 1);
		//Set Material shininessFactor
		glUniform1f(shader->getUniformLocation("material.shininessFactor"), material->ShininessFactor);

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

		uDiffuseTexture = shader->getUniformLocation("material.diffuse");
		uSpecularTexture = shader->getUniformLocation("material.specular");

		shader->finalize();
	}
}
