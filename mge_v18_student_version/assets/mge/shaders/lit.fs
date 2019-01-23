//DIFFUSE COLOR FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininessFactor;
};

struct Light
{
	//Position
	vec4 position;
	
	//Colour
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	//Attenuation
	float constant;
	float linear;
	float quadratic;
};

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

vec3 lightDirection;

in vec3 Normal;
in vec3 FragPos;
in vec2 texCoord;

out vec4 fragment_color;

void main( void ) {
	
	//Ambient;
	vec3 Ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
	
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
	vec3 Diffuse = light.diffuse * lightProjection * vec3(texture(material.diffuse, texCoord));

	//Specular light
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDirection, normalizedNormal);
	
	float spec = pow(max(dot(viewDir, reflectDir),0.0), material.shininessFactor);
	
	vec3 Specular = light.specular * spec * vec3(texture(material.specular, texCoord));

	//Attenuation
	float distance = length(vec3(light.position) - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	Ambient *= attenuation;
	Diffuse *= attenuation;
	Specular *= attenuation;

	vec3 result = (Ambient + Diffuse + Specular);
	fragment_color = vec4 (result,1);
}
