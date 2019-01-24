#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm.hpp"
#include "mge/core/GameObject.hpp"
#include "SFML/Graphics.hpp"

enum LightType { DIRECTIONAL, POINT, SPOTLIGHT };

struct LightingData
{
	LightType Type;
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float Constant;
	float Linear;
	float Quadratic;
	float CutOff;
	float OuterCutOff;
};


/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */
class Light : public GameObject
{
	public:
		Light(	const std::string& aName = nullptr,
			const glm::vec3& aPosition = glm::vec3( 2.0f, 10.0f, 5.0f ),
			LightingData* data = nullptr);
		virtual ~Light();

        //override set parent to register/deregister light...
        virtual void _setWorldRecursively (World* pWorld) override;
		//LightType
		void SetLightType(LightType lightType);
		LightType GetLightType();
		//Ambient
		void SetAmbientColour(glm::vec3 colour);
		glm::vec3 GetAmbientColour();
		//Diffuse
		void SetDiffuseColour(glm::vec3 colour);
		glm::vec3 GetDiffuseColour();
		void SetSpecularColour(glm::vec3 colour);
		glm::vec3 GetSpecularColour();
		void SetLightConstant(float value);
		float GetLightConstant();
		void SetLightLinear(float value);
		float GetLightLinear();
		void SetLightQuadratic(float value);
		float GetLightQuadratic();
		void SetLightCutOff(float value);
		float GetLightCutOff();
		void SetLightOuterCutOff(float value);
		float GetLightOuterCutOff();
		
		glm::vec3 GetForward();

private:
	LightingData* data;

};

#endif // LIGHT_HPP
