#include "ModelBase.h"


//-----------------------------------------------------------------------------
//Constructs the object and sets the number of vertices and elements
//-----------------------------------------------------------------------------
ModelBase::ModelBase(const GLuint program, const char* objPath)
{
	init(program, objPath);
}

//-----------------------------------------------------------------------------
//Sets up the buffers and textures of the objects.
//-----------------------------------------------------------------------------
void ModelBase::init(const GLuint program, const char* objPath)
{
	//Loading object model data
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;

	if (!loadObj(objPath, vertices, texCoords, normals))
	{
		std::cout << ("Failed to load obj file." + *objPath);
	}

	initBuffers(program, vertices, texCoords, normals); 

	NUM_VERTICES = vertices.size(); //set vertex size for draw call
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
// Loads an obj file and populates vertices, texCoords and normals.
// Returns false if failed to load
//-----------------------------------------------------------------------------
bool ModelBase::loadObj(const char * fileName, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_texCoords, std::vector<glm::vec3>& out_normals)
{
	//Create temporary holders
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

		else if (strcmp(lineHeader, "f") == 0)  //if its f
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]); //extract the data as defined in obj file vertex / texture / normal for 3 vertices
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n" + *fileName);
				return false;
			}
			//add it to the respective index arrays
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

		///Process the data indivually since Blender uses indices starting from 1
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