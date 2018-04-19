#pragma once

#include <vector>
#include <fstream>


#include "vgl.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "SOIL.h"

class ModelBase
{
public:
	ModelBase(const GLuint program, const char* objPath, const char* texturePath);

protected:
	int NUM_BUFFERS = 4;
	int NUM_VERTICES = 24;

	GLuint vao;
	GLuint buffers[4];
	GLuint texture;

public:
	
	void draw();

protected:
	void init(const GLuint program, const char* objPath, const char* texturePath);

	void initBuffers(const GLuint program, std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &texCoords, std::vector<glm::vec3> &normals);
	void initTextures(const GLuint program, int width, int height, unsigned char* image);

	bool loadObj(const char* fileName, std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &texCoords, std::vector<glm::vec3> &normals);
};

