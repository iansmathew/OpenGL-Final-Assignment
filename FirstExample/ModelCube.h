#pragma once

#include "vgl.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"


class ModelCube
{
public:
	ModelCube(int _numVertices, int _numElements);
	~ModelCube();

public:
	GLuint vao;
	GLuint buffers[4];
	GLuint texture;

private:
	const int NUM_BUFFERS = 4;
	const int NUM_DRAW_ELEMENTS = 24;
	const int NUM_VERTICES = 24;

public:
	void init(const GLuint program);
	void initBuffers(const GLuint program, const GLfloat* vertices, const GLfloat* colors, GLfloat* texCoords, GLuint* indices);
	void initTextures(const GLuint program, int width, int height, unsigned char* image);
	void draw();

	

};

