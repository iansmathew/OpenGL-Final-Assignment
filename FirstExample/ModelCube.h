#pragma once

#include "vgl.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"


class ModelCube
{
public:
	ModelCube();
	~ModelCube();

public:
GLuint vao;
GLuint buffers[4];
GLuint tex;

private:
const int NUM_BUFFERS = 4;

public:
	void init(const GLuint program);
	void initBuffers(const GLuint program);
	void initTextures(const GLuint program);
	void draw();
	void setupBuffers();

	

};

