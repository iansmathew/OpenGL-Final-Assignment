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

#include "Camera.h"
#include "ModelCube.h"
#include "ModelPyramid.h"

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
glm::vec2 mousePos;
Camera camera;

float radius = 3.0f;
float FOV = 45.0f;
float aspectRatio = 800.0f / 800.0f;

bool keyStates[256];

//Model Objects
ModelPyramid pyramidObject(15, 16);


//-- FUNCTIONS --//

//-----------------------------------------------------------------------------
//Main Function
//-----------------------------------------------------------------------------
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
	glutPassiveMotionFunc(mouseMoveEvent);
	glutKeyboardUpFunc(keyUp);
	glutKeyboardFunc(keyDown);
	glutMainLoop();
}

//-----------------------------------------------------------------------------
//Initialize
//-----------------------------------------------------------------------------
void init()
{
	glEnable(GL_DEPTH_TEST);
	ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER, "triangles.vert" },
	{ GL_FRAGMENT_SHADER, "triangles.frag" },
	{ GL_NONE, NULL }
	};

	shaderProgram = LoadShaders(shaders);
	glUseProgram(shaderProgram);

	initCamera();

	/* Initialize objects here */
	pyramidObject.init(shaderProgram);
}

//-----------------------------------------------------------------------------
//Render function
//-----------------------------------------------------------------------------
void display()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	uploadMatrixToShader();
	/* Draw objects here */
	pyramidObject.draw();


	glutSwapBuffers();
}

//-----------------------------------------------------------------------------
//Frame based loop function
//-----------------------------------------------------------------------------
void timer(int id)
{
	//controlCamera();
	glutPostRedisplay();
	glutTimerFunc(33, timer, 0);
}

//-----------------------------------------------------------------------------
//Mouse move event
//-----------------------------------------------------------------------------
void mouseMoveEvent(int x, int y)
{

	mousePos.x = x;
	mousePos.y = y;
	camera.mouseUpdate(mousePos);
	viewMatrix = camera.getViewMatrix();
	glutPostRedisplay();
}

//-----------------------------------------------------------------------------
//On key down
//-----------------------------------------------------------------------------
void keyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			camera.moveForward();
			break;
		case 's':
			camera.moveBack();
			break;
		case 'd':
			camera.strafeLeft();
			break;
		case 'a':
			camera.strafeRight();
			break;
	}
	glutPostRedisplay();
}

//-----------------------------------------------------------------------------
//On key up
//-----------------------------------------------------------------------------
void keyUp(unsigned char key, int x, int y)
{
	//keyStates[key] = false;
}

//-----------------------------------------------------------------------------
//Move camera with keyboard
//-----------------------------------------------------------------------------
void controlCamera()
{

	if (keyStates['d'])
	{
		camera.strafeLeft();
	}


	if (keyStates['a'])
	{
		camera.strafeRight();
	}


	if (keyStates['w'])
	{
		camera.moveForward();
	}

	if (keyStates['s'])
	{
		camera.moveBack();

	}
}

// -- CAMERA AND VIEW FUNCTIONS -- //
#pragma region CAMERA_AND_VIEW

//-----------------------------------------------------------------------------
//Push the current modelViewMatrix to the stack.
//-----------------------------------------------------------------------------
void pushToStack()
{
	modelViewStack.push_back(modelMatrix);
}

//-----------------------------------------------------------------------------
//Pops the last modelViewMatrix from stack and copies it to the current matrix.
//-----------------------------------------------------------------------------
void popFromStack()
{
	if (modelViewStack.empty())
		throw "Stack is empty.";
	modelMatrix = modelViewStack.back();
	modelViewStack.pop_back();

}

//-----------------------------------------------------------------------------
//Pushes MVP matrix to shader program.
//-----------------------------------------------------------------------------
void uploadMatrixToShader()
{
	glm::mat4 modelViewProjection = glm::mat4(1.0f);
	modelViewProjection = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(uMVP, 1, GL_FALSE, glm::value_ptr(modelViewProjection));
}

//-----------------------------------------------------------------------------
//Initializes camera and sets position
//-----------------------------------------------------------------------------
void initCamera()
{
	uMVP = glGetUniformLocation(shaderProgram, "uMVP");

	///Initializing matrices
	modelMatrix = glm::mat4(1.0f);

	viewMatrix = camera.getViewMatrix();

	projectionMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, 0.1f, 100.0f);

	uploadMatrixToShader();
}

#pragma endregion //CAMERA_AND_VIEW