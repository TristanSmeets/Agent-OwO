#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm.hpp"
#include "mge/core/GameObject.hpp"
#include "SFML/Graphics.hpp"

enum LightType { DIRECTIONAL, POINT };

struct LightingData
{
	LightType Type;
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	float ambientStrength;
	float Constant;
	float Linear;
	float Quadratic;
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
		void SetAmbientStrength(float value);
		float GetAmbientStrength();
		//Diffuse
		void SetDiffuseColour(glm::vec3 colour);
		glm::vec3 GetDiffuseColour();
		void SetLightConstant(float value);
		float GetLightConstant();
		void SetLightLinear(float value);
		float GetLightLinear();
		void SetLightQuadratic(float value);
		float GetLightQuadratic();
		
		
		glm::vec3 GetForward();

private:
	LightingData* data;

};

#endif // LIGHT_HPP
