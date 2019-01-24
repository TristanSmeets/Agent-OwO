//TERRAIN VERTEX SHADER
#version 330

uniform mat4 mvpMatrix;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform sampler2D heightMap;

out vec2 texCoord; //make sure the texture coord is interpolated

void main(void)
{
    vec3 newVertexPosition = vertex;
    newVertexPosition.y =   (2 * normalize(texture(heightMap, uv))).r;
    gl_Position = mvpMatrix * vec4(newVertexPosition, 1.0f);
    texCoord = uv;
}