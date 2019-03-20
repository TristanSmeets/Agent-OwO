//WOBBLE VERTEX SHADER
#version 330

uniform mat4 mvpMatrix;
uniform float time;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec2 texCoord;

void main(void)
{
    vec3 newVertex = vertex;
    float scaleFactor = 0.05f * sin(time) + 0.025f;
    //float scaleFactor = .1f;
    newVertex *=  scaleFactor * sin(gl_VertexID) + 1;
    gl_Position = mvpMatrix * vec4(newVertex, 1.0f);
    texCoord = uv;
}