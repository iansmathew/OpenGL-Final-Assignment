#version 430 core

//Inputs
layout(location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vTexture;
layout (location = 2) in vec3 vNormal;

//Outputs
out vec3 texCoord;
out vec3 normal;
out vec3 fragPos;

//Uniforms
uniform mat4 uMVP;
uniform mat4 model;


void main()
{
	gl_Position = uMVP * vec4(vPosition,1.0f);

	texCoord = vTexture;
	normal = mat3(transpose(inverse(model))) * vNormal;  
	fragPos = vec3(model * vec4(vPosition, 1.0));
}