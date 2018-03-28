#version 430 core
layout(location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTexture;

out vec3 outColor;
out vec2 texCoord;

uniform mat4 uMVP;

void main()
{
	outColor = vColor;
	texCoord = vTexture;
	gl_Position = uMVP * vec4(vPosition, 1.0f);
}
