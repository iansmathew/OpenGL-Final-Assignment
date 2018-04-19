#include "ModelBase.h"


//-----------------------------------------------------------------------------
//Constructs the object and sets the number of vertices and elements
//-----------------------------------------------------------------------------
ModelBase::ModelBase(int _numVertices, int _numDrawElements)
{
	NUM_DRAW_ELEMENTS = _numDrawElements;
	NUM_VERTICES = _numVertices;
}


ModelBase::~ModelBase()
{
}

//-----------------------------------------------------------------------------
//Sets up the buffers and textures of the objects.
//All unique model data is defined within this function.
//Override this function in derived classes using the following template
//The following MUST BE defined and passed into initBuffers & initTextures
//	vertices, colors, texCoords, indices, texWidth, texHeight, texImage
//-----------------------------------------------------------------------------
void ModelBase::init(const GLuint program)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;

	loadObj( "cube.obj", vertices, texCoords, normals);

	//Defining texture
	int width;
	int height;
	unsigned char* image = SOIL_load_image("rubiksTexture.png", &width, &height, 0, SOIL_LOAD_RGB);


	initBuffers(program, vertices, texCoords, normals);
	initTextures(program, width, height, image);

	NUM_VERTICES = vertices.size();
}

//-----------------------------------------------------------------------------
//Initializes and feeds the buffers with model data passed in init
//-----------------------------------------------------------------------------
void ModelBase::initBuffers(const GLuint program, std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &texCoords, std::vector<glm::vec3> &normals)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(3, buffers);

	//Vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	//Texture buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), &texCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);

	//Normal buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(2);
}

//-----------------------------------------------------------------------------
//Initializes the texture and sends it to the uniform
//-----------------------------------------------------------------------------
void ModelBase::initTextures(const GLuint program, int width, int height, unsigned char* image)
{
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glUniform1i(glGetUniformLocation(program, "texture0"), 0);
}

bool ModelBase::loadObj(const char * fileName, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_texCoords, std::vector<glm::vec3>& out_normals)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		printf("Unable to open file: " + *fileName);
		return false;
	}

	while (1)
	{
		char lineHeader[128]; //assuming a single line does not hold more than 128 chars

		int res = fscanf(file, "%s", lineHeader); //read the first word of the line
		if (res == EOF) //if reached EOF
			break;

		//Getting vertices
		if (strcmp(lineHeader, "v") == 0) //if the first word is v
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) //if the first word is vt
		{
			glm::vec2 uvCoord;
			fscanf(file, "%f %f %f\n", &uvCoord.x, &uvCoord.y);
			temp_uvs.push_back(uvCoord);
		}
		else if (strcmp(lineHeader, "vn") == 0) //if the first word is vn
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}

		else if (strcmp(lineHeader, "f") == 0) 
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}

		//Process the data indivually since Blender uses indices starting from 1
		for (unsigned int i = 0; i < vertexIndices.size(); i++)
		{
			unsigned int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			out_vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < uvIndices.size(); i++)
		{
			unsigned int uvIndex = uvIndices[i];
			glm::vec2 uv = temp_uvs[uvIndex - 1];
			out_texCoords.push_back(uv);
		}

		for (unsigned int i = 0; i < normalIndices.size(); i++)
		{
			unsigned int normalIndex = normalIndices[i];
			glm::vec3 normal = temp_normals[normalIndex - 1];
			out_normals.push_back(normal);
		}
		
	}
}

//-----------------------------------------------------------------------------
//Draws the model with defined NUM_DRAW_ELEMENTS
//-----------------------------------------------------------------------------
void ModelBase::draw()
{
	glBindVertexArray(vao); //bind to the objects vao
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]); //bind to the index buffer
	glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);
}