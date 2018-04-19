#version 430 core

in vec2 texCoord;

out vec4 fColor;

uniform sampler2D texture0;

void main()
{
	//fColor = vec4(outColor, 1.0f);
	//fColor = vec4(0.5f, 0.7f, 0.1f, 1.0f);
	fColor = texture(texture0, texCoord);
}