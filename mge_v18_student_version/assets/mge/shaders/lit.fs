//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

struct Light
{
	//Position
	vec4 position;
	
	//Colours
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	//Strengths
	float ambientStrength;
	float specularStrength;
	int shininessFactor;

	//Attenuation
	float constant;
	float linear;
	float quadratic;
};

uniform Light light;
uniform vec3 viewPos;
uniform vec3 objectColour;

vec3 lightDirection;

in vec3 Normal;
in vec3 FragPos;

out vec4 fragment_color;

void main( void ) {
	
	//Ambient;
	vec3 ambient = light.ambient * light.ambientStrength;
	
	//Diffuse
	vec3 normalizedNormal = normalize(Normal);
	//Checking if a position or a direction is being passed.
	if(light.position.w == 1)
	{
		lightDirection = normalize(vec3(light.position) - FragPos);
	}
	else if(light.position.w == 0)
	{
		lightDirection = normalize(vec3(-light.position));
	}
	//Calculating the projection of the lightDirection on normalized normals
	float lightProjection = max(dot(normalizedNormal, lightDirection), 0.0);
	vec3 diffuse = lightProjection * light.diffuse;

	//Specular light
	vec3 viewDir = normalize(-viewPos - FragPos);
	vec3 reflectDir = reflect(lightDirection, normalizedNormal);
	
	float spec = pow(max(dot(viewDir, reflectDir),0.0), light.shininessFactor);
	
	vec3 specular = light.specularStrength * spec * light.specular;

	//Attenuation
	float distance = length(vec3(light.position) - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = (ambient + diffuse + specular) * objectColour;
	fragment_color = vec4 (result,1);
}
