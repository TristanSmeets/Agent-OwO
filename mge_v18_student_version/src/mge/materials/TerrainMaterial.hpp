#ifndef TERRAINMATERIAL_HPP
#define TERRAINMATERIAL_HPP

#include "GL/glew.h"
#include "mge/materials/AbstractMaterial.hpp"

class ShaderProgram;
class Texture;

struct TerrainTexture
{
	Texture* Diffuse1;
	Texture* Diffuse2;
	Texture* Diffuse3;
	Texture* Diffuse4;
	Texture* HeightMap;
	Texture* SplatMap;
};


class TerrainMaterial : public AbstractMaterial
{
public:
	TerrainMaterial(TerrainTexture* terrainTexture);
	virtual ~TerrainMaterial();

	void SetTerrainTexture(TerrainTexture* terrainTexture);

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;
	
private:
	static ShaderProgram* shader;
	static void lazyInitializeShader();
	void setTextureSlot(Texture* texture, GLint uniform, int slotID);

	//Cache all identifiers for uniforms & attributes
	static GLint uMVPMatrix;
	static GLint uDiffuseTexture1;
	static GLint uDiffuseTexture2;
	static GLint uDiffuseTexture3;
	static GLint uDiffuseTexture4;
	static GLint uHeightMap;
	static GLint uSplatMap;
	static GLint uTime;
	
	static GLint aVertex;
	static GLint aNormal;
	static GLint aUV;

	TerrainTexture* terrainTexture;

	TerrainMaterial(const TerrainMaterial&);
};

#endif
