//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform vec3 ambientColour;
uniform vec3 lightPosition;
uniform vec3 lightColour;
uniform float ambientStrength;

in vec3 Normal;
in vec3 FragPos;

out vec4 fragment_color;

void main( void ) {
	
	vec3 ambient = ambientStrength * lightColour;
	
	vec3 normalizedNormal = normalize(Normal);
	vec3 lightDirection = normalize(lightPosition - FragPos);

	float difference = max(dot(normalizedNormal, lightDirection), 0.0);
	vec3 diffuse = difference * lightColour;

	vec3 result = (ambient + diffuse) * ambientColour;
	fragment_color = vec4 (result,1);
}
