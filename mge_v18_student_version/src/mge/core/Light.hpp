#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm.hpp"
#include "mge/core/GameObject.hpp"
#include "SFML/Graphics.hpp"

enum LightType { DIRECTIONAL, POINT };

/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */
class Light : public GameObject
{
	public:
		Light(const std::string& aName = nullptr, 
			const glm::vec3& aPosition = glm::vec3( 2.0f, 10.0f, 5.0f ),
			LightType lightType = LightType::DIRECTIONAL,
			glm::vec3 ambientColour = glm::vec3(1,1,1),
			glm::vec3 diffuseColour = glm::vec3(1,1,1),
			float intensity = 1.0f);
		virtual ~Light();

        //override set parent to register/deregister light...
        virtual void _setWorldRecursively (World* pWorld) override;
		//LightType
		void SetLightType(LightType lightType);
		LightType GetLightType();
		//Colour
		void SetAmbientColour(glm::vec3 colour);
		glm::vec3 GetAmbientColour();
		void SetDiffuseColour(glm::vec3 colour);
		glm::vec3 GetDiffuseColour();
		//Intensity
		void SetIntensity(float value);
		float GetIntensity();
		glm::vec3 GetForward();

private:
	LightType lightType;
	glm::vec3 ambientColour;
	glm::vec3 diffuseColour;
	float intensity;

};

#endif // LIGHT_HPP
