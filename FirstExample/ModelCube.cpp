#include "ModelCube.h"
#include "SOIL.h"


ModelCube::ModelCube(int _numVertices, int _numElements) :
	ModelBase(_numVertices, _numElements)
{
	
}


ModelCube::~ModelCube()
{
}

//-----------------------------------------------------------------------------
//Overriding the base init and feeding unique model data
//-----------------------------------------------------------------------------
void ModelCube::init(GLuint program)
{

	//Defining the vertices, colors and indices for the object

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

	//Defining texture
	int width;
	int height;
	unsigned char* image = SOIL_load_image("rubiksTexture.png", &width, &height, 0, SOIL_LOAD_RGB);


	initBuffers(program, vertices, colors, texCoords, indices);
	initTextures(program, width, height, image);
}
