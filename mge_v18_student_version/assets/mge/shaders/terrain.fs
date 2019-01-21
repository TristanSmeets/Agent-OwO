//TERRAIN FRAGMENT SHADER
#version 330

uniform sampler2D diffuseTexture1;
uniform sampler2D diffuseTexture2;
uniform sampler2D diffuseTexture3;
uniform sampler2D diffuseTexture4;
uniform sampler2D splatMap;
uniform float time;

in vec2 texCoord;

out vec4 fragmentColour;

void main (void)
{
    vec4 splatTexture = texture2D(splatMap, texCoord);
    vec4 diffuse1 = texture2D(diffuseTexture1, texCoord);
    vec4 diffuse2 = texture2D(diffuseTexture2, texCoord * cos(time)) ;
    vec4 diffuse3 = texture2D(diffuseTexture3, texCoord);
    vec4 diffuse4 = texture2D(diffuseTexture4, texCoord);

    diffuse1 *= splatTexture.r;
    diffuse2 = mix(diffuse1, diffuse2, splatTexture.g);
    diffuse3 = mix(diffuse2, diffuse3, splatTexture.b);
    vec4 outColour = vec4(mix(diffuse3, diffuse4, splatTexture.a));
    outColour.w = 1;

    fragmentColour = outColour;
}