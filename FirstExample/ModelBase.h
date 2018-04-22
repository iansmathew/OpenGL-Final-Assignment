#pragma once

#include <vector>
#include <fstream>


#include "vgl.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include <iostream>
#include "SOIL.h"

class ModelBase
{
public:
	ModelBase(const GLuint program, const char* objPath);

protected:
	int NUM_BUFFERS = 4;
	int NUM_VERTICES = 24;

	GLuint vao;
	GLuint buffers[4];
	GLuint texture;

public:
	
	void draw();

protected:
	void init(const GLuint program, const char* objPath);

	void initBuffers(const GLuint program, std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &texCoords, std::vector<glm::vec3> &normals);

	bool loadObj(const char* fileName, std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &texCoords, std::vector<glm::vec3> &normals);
};

