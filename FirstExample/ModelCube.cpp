#include "ModelCube.h"
#include "SOIL.h"


ModelCube::ModelCube()
{
}


ModelCube::~ModelCube()
{
}

void ModelCube::init(const GLuint program)
{
	initBuffers(program);
	initTextures(program);
}

void ModelCube::initBuffers(const GLuint program)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(4, buffers);

	GLfloat vertices[] =
	{
		-0.45f, -0.45f,  0.45f,	//v0
		0.45f, -0.45f,  0.45f,	//v1
		0.45f,  0.45f,  0.45f,	//v2
		-0.45f,  0.45f,  0.45f,	//v3 //front

		-0.45f, -0.45f, -0.45f,	//v4 
		0.45f, -0.45f, -0.45f,	//v5
		0.45f,  0.45f, -0.45f,	//v6
		-0.45f,  0.45f, -0.45f,	//v7 //back

		0.45f, -0.45f,  0.45f,	//v1 8
		0.45f, -0.45f, -0.45f,	//v5 9
		0.45f,  0.45f, -0.45f,	//v6 10 
		0.45f,  0.45f,  0.45f,	//v2 11

		-0.45f, -0.45f, -0.45f,	//v4 12
		-0.45f, -0.45f,  0.45f,	//v0 13
		-0.45f,  0.45f,  0.45f,	//v3 14
		-0.45f,  0.45f, -0.45f,	//v7 15

		-0.45f,  0.45f,  0.45f,	//v3 16
		0.45f,  0.45f,  0.45f,	//v2 17
		0.45f,  0.45f, -0.45f,	//v6 18
		-0.45f,  0.45f, -0.45f,	//v7 19

		-0.45f, -0.45f, -0.45f,	//v4 20
		0.45f, -0.45f, -0.45f,	//v5 21
		0.45f, -0.45f,  0.45f,	//v1 22
		-0.45f, -0.45f, 0.45f, //v0 23
	};

	//Vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	GLfloat colors[] =
	{
		-0.45f, -0.45f,  0.45f,	//v0
		0.45f, -0.45f,  0.45f,	//v1
		0.45f,  0.45f,  0.45f,	//v2
		-0.45f,  0.45f,  0.45f,	//v3 //front

		-0.45f, -0.45f, -0.45f,	//v4 
		0.45f, -0.45f, -0.45f,	//v5
		0.45f,  0.45f, -0.45f,	//v6
		-0.45f,  0.45f, -0.45f,	//v7 //back

		0.45f, -0.45f,  0.45f,	//v1 8
		0.45f, -0.45f, -0.45f,	//v5 9
		0.45f,  0.45f, -0.45f,	//v6 10 
		0.45f,  0.45f,  0.45f,	//v2 11

		-0.45f, -0.45f, -0.45f,	//v4 12
		-0.45f, -0.45f,  0.45f,	//v0 13
		-0.45f,  0.45f,  0.45f,	//v3 14
		-0.45f,  0.45f, -0.45f,	//v7 15

		-0.45f,  0.45f,  0.45f,	//v3 16
		0.45f,  0.45f,  0.45f,	//v2 17
		0.45f,  0.45f, -0.45f,	//v6 18
		-0.45f,  0.45f, -0.45f,	//v7 19

		-0.45f, -0.45f, -0.45f,	//v4 20
		0.45f, -0.45f, -0.45f,	//v5 21
		0.45f, -0.45f,  0.45f,	//v1 22
		-0.45f, -0.45f, 0.45f, //v0 23
	};

	//Color buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);

	GLfloat texCoords[] =
	{
		0.25f, 0.6666666f, //front
		0.50f, 0.6666666f,
		0.50f, 0.3333333f,
		0.25f, 0.3333333f,

		0.75f, 0.6666666f, //back
		1.0f, 0.6666666f,
		1.0f, 0.3333333f,
		0.75f, 0.3333333f,

		0.50f, 0.6666666f, //right
		0.75f, 0.6666666f,
		0.75, 0.3333333f,
		0.50f, 0.3333333f,

		0.0f, 0.6666666f, //left
		0.25f, 0.6666666f,
		0.25f, 0.3333333f,
		0.0f, 0.3333333f,

		0.25f, 0.33333333f, //top
		0.50f, 0.3333333f,
		0.50f, 0.0f,
		0.25f, 0.0f,

		0.25f, 0.999999999f, //bottom
		0.50f, 0.99999999f,
		0.50f, 0.66666666f,
		0.25f, 0.6666666f,
	};

	//Texture buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(2);

	GLuint indices[] = 
	{
		0, 1, 2, //front
		0, 2, 3,
		5, 4, 7, //back
		5, 7, 6,
		8, 9, 10, //right
		8, 10, 11,
		12, 13, 14, //left
		12, 14, 15,
		16, 17, 18,
		16, 18, 19,
		20, 21, 22,
		20, 22, 23
	};

	//Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void ModelCube::initTextures(const GLuint program)
{
	GLint width = 480;
	GLint height = 360;
	unsigned char* image = SOIL_load_image("rubiksTexture.png", &width, &height, 0, SOIL_LOAD_RGB);


	glGenTextures(1, &tex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glUniform1i(glGetUniformLocation(program, "texture0"), 0);
}

void ModelCube::draw()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[3]);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void ModelCube::setupBuffers()
{
}
