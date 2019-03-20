#include "glm.hpp"

#include "TerrainMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

GLint TerrainMaterial::uMVPMatrix = 0;
GLint TerrainMaterial::uDiffuseTexture1 = 0;
GLint TerrainMaterial::uDiffuseTexture2 = 0;
GLint TerrainMaterial::uDiffuseTexture3 = 0;
GLint TerrainMaterial::uDiffuseTexture4 = 0;
GLint TerrainMaterial::uHeightMap = 0;
GLint TerrainMaterial::uSplatMap = 0;
GLint TerrainMaterial::uTime = 0;
GLint TerrainMaterial::aVertex = 0;
GLint TerrainMaterial::aNormal = 0;
GLint TerrainMaterial::aUV = 0;

ShaderProgram* TerrainMaterial::shader = NULL;

TerrainMaterial::TerrainMaterial(TerrainTexture* terrain) : terrainTexture(terrain)
{
	lazyInitializeShader();
}

TerrainMaterial::~TerrainMaterial()
{
	delete terrainTexture;
	delete shader;
}

void TerrainMaterial::SetTerrainTexture(TerrainTexture * terrainTexture)
{
	this->terrainTexture = terrainTexture;
}

void TerrainMaterial::render(World * pWorld, Mesh * pMesh, const glm::mat4 & pModelMatrix, const glm::mat4 & pViewMatrix, const glm::mat4 & pProjectionMatrix)
{
	if (!terrainTexture) return;

	shader->use();

	//HeightMap
	setTextureSlot(terrainTexture->HeightMap, uHeightMap, 0);

	//SplatMap
	setTextureSlot(terrainTexture->SplatMap, uSplatMap, 6);

	//Diffuse1
	setTextureSlot(terrainTexture->Diffuse1, uDiffuseTexture1, 2);

	//Diffuse2
	setTextureSlot(terrainTexture->Diffuse2, uDiffuseTexture2, 3);
	
	//Diffuse3
	setTextureSlot(terrainTexture->Diffuse3, uDiffuseTexture3, 4);
	
	//Diffuse4
	setTextureSlot(terrainTexture->Diffuse4, uDiffuseTexture4, 5);
	
	//Set time Uniform
	glUniform1f(uTime, clock() / 1000.0f);

	//pass in a precalculated mvp matrix
	glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
	glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	//Inform mesh where to stream data
	pMesh->streamToOpenGL(aVertex, aNormal, aUV);
}

void TerrainMaterial::lazyInitializeShader()
{
	if (!shader)
	{
		shader = new ShaderProgram();
		shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "terrain.vs");
		shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "terrain.fs");
		shader->finalize();

		uMVPMatrix = shader->getUniformLocation("mvpMatrix");
		uDiffuseTexture1 = shader->getUniformLocation("diffuseTexture1");
		uDiffuseTexture2 = shader->getUniformLocation("diffuseTexture2");
		uDiffuseTexture3 = shader->getUniformLocation("diffuseTexture3");
		uDiffuseTexture4 = shader->getUniformLocation("diffuseTexture4");
		uHeightMap = shader->getUniformLocation("heightMap");
		uSplatMap = shader->getUniformLocation("splatMap");

		uTime = shader->getUniformLocation("time");

		aVertex = shader->getAttribLocation("vertex");
		aNormal = shader->getAttribLocation("normal");
		aUV = shader->getAttribLocation("uv");
	}
}

void TerrainMaterial::setTextureSlot(Texture * texture, GLint uniform, int slotID)
{
	//Setup the texure slot with a certain slotID
	glActiveTexture(GL_TEXTURE0 + slotID);
	//Bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, texture->getId());
	//Tell the shader the texture slot for the diffuse texture.
	glUniform1i(uniform, slotID);
}
