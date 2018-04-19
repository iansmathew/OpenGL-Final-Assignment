#version 430 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexture;
layout (location = 2) in vec3 vNormal;

out vec2 texCoord;

uniform mat4 uMVP;

void main()
{
	texCoord = vTexture;
	gl_Position = uMVP * vec4(vPosition, 1.0f);
}
