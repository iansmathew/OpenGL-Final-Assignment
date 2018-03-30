#pragma once

#include "vgl.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "SOIL.h"

class ModelBase
{
public:
	ModelBase(int _numVertices, int _numDrawElements);
	~ModelBase();

protected:
	GLuint vao;
	GLuint buffers[4];
	GLuint texture;
	int NUM_BUFFERS = 4;
	int NUM_DRAW_ELEMENTS = 24;
	int NUM_VERTICES = 24;

public:
	virtual void init(const GLuint program) = 0;
	void draw();

protected:
	void initBuffers(const GLuint program, const GLfloat vertices[], const GLfloat colors[], GLfloat texCoords[], GLuint indices[]);
	void initTextures(const GLuint program, int width, int height, unsigned char* image);
};

