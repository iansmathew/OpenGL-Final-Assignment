#version 430 core

//Inputs
in vec3 texCoord;
in vec3 normal;
in vec3 fragPos;

//Outputs
out vec4 fColor;

//Uniforms
uniform highp sampler2D texture0;

uniform highp vec3 lightPos; 
uniform highp vec3 lightColor;
uniform highp vec3 viewPos;
uniform highp float ambientStrength;
uniform highp float specularStrength;
uniform highp float diffuseStrength;

void main()
{	
	//Calculating texture mapping
	vec4 tex = texture(texture0, texCoord.xy);

	//Calculating ambient strength
	vec3 ambient = ambientStrength * lightColor;

	//Calculating diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor * diffuseStrength;

	//Calculating specular 
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor; 
	
	vec3 lightResult = ambient + diffuse + specular;

	//Final color
	fColor = tex + vec4(lightResult, 1.0f);
}