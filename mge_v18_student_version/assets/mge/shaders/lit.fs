//DIFFUSE COLOR FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininessFactor;
};

struct Light
{
	//LightType
	int type;		//0: Direction; 1: Point; 2: Spotlight

	//Position
	vec3 position;
	vec3 direction;

	//Spotlight
	float cutOff;
	float outerCutOff;

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


float calculateAttenuation(in Light light, in vec3 fragPos)
{
	float distance = length(vec3(light.position) - fragPos);
	return 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
}

vec3 createLightDirection(in Light light, in vec3 fragPos)
{
	if(light.type == 0)
	{
		return normalize(-light.direction);
	}
	else
	{
		return normalize(light.position - fragPos);
	}
}

float createSpecularStrength(in vec3 viewPos, in vec3 fragPos, in vec3 lightDir, in vec3 normal, in Material material)
{
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	return pow(max(dot(viewDir, reflectDir),0.0), material.shininessFactor);
}

vec3 createAmbient(in Light light, in Material material, in vec2 texCoord)
{
	return light.ambient * vec3(texture(material.diffuse, texCoord));
}

vec3 createDiffuse(in Light light, in Material material, in vec3 lightDirection, in vec3 normal,in vec2 texCoord)
{
	float lightProjection = max(dot(normal, lightDirection), 0.0);
	return light.diffuse * lightProjection * vec3(texture(material.diffuse, texCoord));
}

vec3 createSpecular(in Light light, in Material material, in vec2 texCoord,in float specularStrength)
{
	return light.specular * specularStrength * vec3(texture(material.specular, texCoord));
}

void main( void ) {

	vec3 normalizedNormal = normalize(Normal);
	lightDirection = createLightDirection(light, FragPos);
	vec3 Ambient = createAmbient(light, material, texCoord);
	vec3 Diffuse = createDiffuse(light, material, lightDirection, normalizedNormal, texCoord);
	float spec = createSpecularStrength(viewPos, FragPos, lightDirection, normalizedNormal, material);
	vec3 Specular = createSpecular(light, material, texCoord, spec);
	float attenuation = calculateAttenuation(light, FragPos);
	Ambient *= attenuation;
	Diffuse *= attenuation;
	Specular *= attenuation;
	
	if(light.type == 2)
	{
		float theta = dot(lightDirection, normalize(-light.direction));
		float epsilon = light.cutOff - light.outerCutOff;
		float intensity = clamp((theta - light.outerCutOff) / epsilon, 0, 1);

		if(theta > light.cutOff)
		{
			Diffuse *= intensity;
			Specular *= intensity;
			vec3 result = (Ambient + Diffuse + Specular);
			fragment_color = vec4(result,1);
		}
		else
		{
			fragment_color = vec4(Ambient, 1);
		}
	}	
	else
	{
		vec3 result = (Ambient + Diffuse + Specular);
		fragment_color = vec4 (result,1);
	}

	
}

