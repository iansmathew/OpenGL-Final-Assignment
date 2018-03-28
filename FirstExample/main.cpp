//***************************************************************************
// main.cpp by Ian Sebastian Mathew & Diego Camacho (C) 2018 All Rights Reserved.
// 
// Final Assignment submission.
// 
// Description:
//	- Click run to see the results
//  - A & D keys - Move left right
//	- W & S keys - Move forward and backwards
//	- R & F keys - Move up and down
//*****************************************************************************

#include <iostream>
#include <list>
#include "vgl.h"
#include "LoadShaders.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtx\rotate_vector.hpp"
#include "SOIL.h"

#include "ModelCube.h"

#include "main.h"

//Program pointers
GLuint shaderProgram;
GLuint uMVP; 

//Matrices
std::list<glm::mat4> modelViewStack;
glm::mat4 projectionMatrix;
glm::mat4 modelMatrix;
glm::mat4 viewMatrix;

//Camera properties
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 camInitialPos = glm::vec3(0.0f, 0.0f, 10.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); //let camera point towards origin.
glm::vec3 cameraDirection = glm::normalize(camInitialPos - cameraTarget); //z-axis forward of camera. Faces opposite direction of cameraTarget.
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));
glm::vec3 cameraPos = camInitialPos;

float radius = 3.0f;
float FOV = 45.0f;
float aspectRatio = 800.0f / 800.0f;

//Model Objects
ModelCube cubeObject;


//-- FUNCTIONS --//

/*
	Main Function
*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glEnable(GL_DEPTH_TEST);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	glutInitWindowSize(800, 800);
	glutCreateWindow("Final Assignment");
	glewInit();

	init();

	glutDisplayFunc(display);
	glutTimerFunc(33.3, timer, 0);
	glutMainLoop();
}

/*
	Initialize
*/

void init()
{
	glEnable(GL_DEPTH_TEST);
	ShaderInfo shaders[] = 
	{
		{GL_VERTEX_SHADER, "triangles.vert"},
		{GL_FRAGMENT_SHADER, "triangles.frag"},
		{GL_NONE, NULL}
	};

	shaderProgram = LoadShaders(shaders);
	glUseProgram(shaderProgram);

	initCamera();
	cubeObject.init(shaderProgram);
}

/*
	Render function
*/

void display()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw objects
	cubeObject.draw();

	glutSwapBuffers();

}

/*
	Frame based loop function
*/
void timer(int id)
{

}

// -- CAMERA AND VIEW FUNCTIONS -- //
#pragma region CAMERA_AND_VIEW

// Push the current modelViewMatrix to the stack.
void pushToStack()
{
	modelViewStack.push_back(modelMatrix);
}

//Pops the last modelViewMatrix from stack and copies it to the current matrix.
void popFromStack()
{
	if (modelViewStack.empty())
		throw "Stack is empty.";
	modelMatrix = modelViewStack.back();
	modelViewStack.pop_back();

}


//Pushes MVP matrix to shader program.
void uploadMatrixToShader()
{
	glm::mat4 modelViewProjection = glm::mat4(1.0f);
	modelViewProjection = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(uMVP, 1, GL_FALSE, glm::value_ptr(modelViewProjection));
}

void initCamera()
{
	uMVP = glGetUniformLocation(shaderProgram, "uMVP");

	///Initializing matrices
	modelMatrix = glm::mat4(1.0f);

	viewMatrix = glm::lookAt(camInitialPos, cameraTarget, up);

	projectionMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, 0.1f, 100.0f);

	uploadMatrixToShader();
}

#pragma endregion //CAMERA_AND_VIEW