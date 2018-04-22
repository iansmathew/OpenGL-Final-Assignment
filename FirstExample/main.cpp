//***************************************************************************
// main.cpp by Ian Sebastian Mathew & Diego Camacho (C) 2018 All Rights Reserved.
// 
// Final Assignment submission.
// 
// Description:
//	- Move camera with WASD and mouse to look around
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
#include "ShapeGenerator.h"
#include "TextureLoader.h"
#include "main.h"

//Program pointers
GLuint shaderProgram;
GLuint uMVP;
GLuint uModelMatrix;

//Light Attributes
float ambientStrength = 0.1f;
float specularStrength = 0.25f;
float diffuseStrength  = 0.5f;
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 lightPosition = { 10.0f, 10.0f, 10.0f };

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
float aspectRatio = 1920.f / 1080.f;

bool keyStates[256];

//Objects
ShapeGenerator shapeGenerator;
TextureLoader textureLoader;

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

	glutInitWindowSize(1920, 1080);
	glutCreateWindow("Final Assignment");
	glewInit();

	init();

	glutDisplayFunc(display);
	glutTimerFunc(1000.0 / 60.0, timer, 0);
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
	initLights();
	shapeGenerator.init(shaderProgram);
	/* Initialize objects here */

	textureLoader.init();
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
	pushToStack();

	drawDemoShapes();

	glutSwapBuffers();
}

//-----------------------------------------------------------------------------
//Frame based loop function
//-----------------------------------------------------------------------------
void timer(int id)
{
	controlCamera();
	glutPostRedisplay();
	glutTimerFunc(1000.0 / 60.0, timer, 0);
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
	keyStates[key] = true;
}

//-----------------------------------------------------------------------------
//On key up
//-----------------------------------------------------------------------------
void keyUp(unsigned char key, int x, int y)
{
	keyStates[key] = false;
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
	glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}


//-----------------------------------------------------------------------------
//Initializes lights and uniform pointers
//-----------------------------------------------------------------------------
void initLights()
{
	GLuint uAmbientStrength = glGetUniformLocation(shaderProgram, "ambientStrength");
	glUniform1f(uAmbientStrength, ambientStrength);

	GLuint uSpecularStrength = glGetUniformLocation(shaderProgram, "specularStrength");
	glUniform1f(uSpecularStrength, specularStrength);


	GLuint uDiffuseStrength = glGetUniformLocation(shaderProgram, "diffuseStrength");
	glUniform1f(uDiffuseStrength, diffuseStrength);

	GLuint uLightColor = glGetUniformLocation(shaderProgram, "lightColor");
	glUniform3fv(uLightColor, 1, glm::value_ptr(lightColor));

	GLuint uLightPos = glGetUniformLocation(shaderProgram, "lightPos");
	glUniform3fv(uLightPos, 1, glm::value_ptr(lightPosition));

	GLuint uViewPos = glGetUniformLocation(shaderProgram, "viewPos");
	glUniform3fv(uViewPos, 1, glm::value_ptr(camera.getCameraPosition()));
}

//-----------------------------------------------------------------------------
//Initializes camera and sets position
//-----------------------------------------------------------------------------
void initCamera()
{
	uMVP = glGetUniformLocation(shaderProgram, "uMVP");
	uModelMatrix = glGetUniformLocation(shaderProgram, "model");

	///Initializing matrices
	modelMatrix = glm::mat4(1.0f);

	viewMatrix = camera.getViewMatrix();

	projectionMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, 0.1f, 100.0f);

	uploadMatrixToShader();
}

//-----------------------------------------------------------------------------
//Move camera with keyboard
//-----------------------------------------------------------------------------
void controlCamera()
{
	if (keyStates['w'])
		camera.moveForward();
	if (keyStates['s'])
		camera.moveBack();
	if (keyStates['a'])
		camera.strafeLeft();
	if (keyStates['d'])
		camera.strafeRight();

	viewMatrix = camera.getViewMatrix();
	GLuint uViewPos = glGetUniformLocation(shaderProgram, "viewPos");
	glUniform3fv(uViewPos, 1, glm::value_ptr(camera.getCameraPosition()));
}

#pragma endregion //CAMERA_AND_VIEW

void drawDemoShapes()
{
	//Floor
	textureLoader.loadTexture(shaderProgram, Textures::GRASS);
	pushToStack();
	uploadMatrixToShader();
	TranslateRotateScale(glm::vec3(0.0f, -5.0f, 0.0f), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	shapeGenerator.drawPlane();
	popFromStack();

	//Hexagon Pillars
	textureLoader.loadTexture(shaderProgram, Textures::STONE);
	pushToStack();
	TranslateRotateScale(glm::vec3(4.0f, 2.0f, 4.0f), -10.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f,2.0f,1.0f));
	uploadMatrixToShader();

	shapeGenerator.drawHexagon();
	popFromStack();

	pushToStack();
	TranslateRotateScale(glm::vec3(4.0f, 2.0f, -4.0f), 10.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 2.0f, 1.0f));
	uploadMatrixToShader();

	shapeGenerator.drawHexagon();
	popFromStack();

	pushToStack();
	TranslateRotateScale(glm::vec3(-4.0f, 2.0f, 4.0f), -10.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 2.0f, 1.0f));
	uploadMatrixToShader();

	shapeGenerator.drawHexagon();
	popFromStack();

	pushToStack();
	TranslateRotateScale(glm::vec3(-4.0f, 2.0f, -4.0f), 10.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 2.0f, 1.0f));
	uploadMatrixToShader();

	shapeGenerator.drawHexagon();
	popFromStack();

	//Pillars HalfTop

	pushToStack();
	TranslateRotateScale(glm::vec3(4.0f, 4.0f, 4.0f), -10.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	uploadMatrixToShader();

	shapeGenerator.drawCutCone();
	popFromStack();

	pushToStack();
	TranslateRotateScale(glm::vec3(4.0f, 4.0f, -4.0f), 10.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	uploadMatrixToShader();

	shapeGenerator.drawCutCone();
	popFromStack();

	pushToStack();
	TranslateRotateScale(glm::vec3(-4.0f, 4.0f, 4.0f), -10.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	uploadMatrixToShader();

	shapeGenerator.drawCutCone();
	popFromStack();

	pushToStack();
	TranslateRotateScale(glm::vec3(-4.0f, 4.0f, -4.0f), 10.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	uploadMatrixToShader();

	shapeGenerator.drawCutCone();
	popFromStack();

	//Pillar Top
	textureLoader.loadTexture(shaderProgram, Textures::GOLD);
	pushToStack();
	TranslateRotateScale(glm::vec3(4.0f, 6.0f, 4.0f), -10.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.8f, 1.2f, 0.8f));
	uploadMatrixToShader();
	
	shapeGenerator.drawCone();
	popFromStack();


	pushToStack();
	TranslateRotateScale(glm::vec3(4.0f, 6.0f, -4.0f), 10.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.8f, 1.2f, 0.8f));
	uploadMatrixToShader();

	shapeGenerator.drawCone();
	popFromStack();


	pushToStack();
	TranslateRotateScale(glm::vec3(-4.0f, 6.0f, 4.0f), -10.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.8f, 1.2f, 0.8f));
	uploadMatrixToShader();

	shapeGenerator.drawCone();
	popFromStack();


	pushToStack();
	TranslateRotateScale(glm::vec3(-4.0f, 6.0f, -4.0f), 10.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.8f, 1.2f, 0.8f));
	uploadMatrixToShader();

	shapeGenerator.drawCone();
	popFromStack();

	//Castle Walls
	textureLoader.loadTexture(shaderProgram, Textures::STONE);
	pushToStack();
	TranslateRotateScale(glm::vec3(-4.0f, 2.0, 0), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(.2f, 2.0f, 3.15f));
	uploadMatrixToShader();

	shapeGenerator.drawCube();
	popFromStack();

	pushToStack();
	TranslateRotateScale(glm::vec3(4.0f, 2.0, 0), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(.2f, 2.0f, 3.15f));
	uploadMatrixToShader();

	shapeGenerator.drawCube();
	popFromStack();

	pushToStack();
	TranslateRotateScale(glm::vec3(0.0f, 2.0, -4.0), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(3.15f, 2.0f, .2f));
	uploadMatrixToShader();

	shapeGenerator.drawCube();
	popFromStack();

	//-->Front Wall

	pushToStack();
	TranslateRotateScale(glm::vec3(-2.5, 2.0, 4.0), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.05f, 2.0f, .2f));
	uploadMatrixToShader();

	shapeGenerator.drawCube();
	popFromStack();

	pushToStack();
	TranslateRotateScale(glm::vec3(2.5, 2.0, 4.0), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.05f, 2.0f, .2f));
	uploadMatrixToShader();

	shapeGenerator.drawCube();
	popFromStack();

	pushToStack();
	TranslateRotateScale(glm::vec3(0, 3.0, 4.0), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.45, 1.3, .2f));
	uploadMatrixToShader();

	shapeGenerator.drawCube();
	popFromStack();

	//Middle Stand

	textureLoader.loadTexture(shaderProgram, Textures::COOBLESTONE);

	pushToStack();
	TranslateRotateScale(glm::vec3(0, 0.4f, 0), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.5f, 0.8, 0.5f));
	uploadMatrixToShader();

	shapeGenerator.drawFrustum();
	popFromStack();


	//Diamond

	textureLoader.loadTexture(shaderProgram, Textures::SILVER);

	pushToStack();
	TranslateRotateScale(glm::vec3(0, 3.0f, 0), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	uploadMatrixToShader();

	shapeGenerator.drawDiamond();
	popFromStack();

	//Diamond Top

	textureLoader.loadTexture(shaderProgram, Textures::GOLD);

	pushToStack();
	TranslateRotateScale(glm::vec3(0, 5.0f, 0), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	uploadMatrixToShader();

	shapeGenerator.drawTorus();
	popFromStack();

	//Wedges

	textureLoader.loadTexture(shaderProgram, Textures::WOOD);

	pushToStack();
	TranslateRotateScale(glm::vec3(2.0f, 0.5, 0), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	uploadMatrixToShader();

	shapeGenerator.drawWedge();
	popFromStack();

	pushToStack();
	TranslateRotateScale(glm::vec3(-2.0f, 0.5, 0), -90.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	uploadMatrixToShader();

	shapeGenerator.drawWedge();
	popFromStack();

	pushToStack();
	TranslateRotateScale(glm::vec3(0.0f, 0.5, -2.0f), 180.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	uploadMatrixToShader();

	shapeGenerator.drawWedge();
	popFromStack();

	//Half_Hexagons

	pushToStack();
	TranslateRotateScale(glm::vec3(0.0f, 4.3f, -4.0), 180.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.8, .2f));
	uploadMatrixToShader();

	shapeGenerator.drawHalfHexagon();
	popFromStack();

	pushToStack();
	TranslateRotateScale(glm::vec3(4.0, 4.3f, 0.0f), 180.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(.2f, 0.8, 1.0f));
	uploadMatrixToShader();

	shapeGenerator.drawHalfHexagon();
	popFromStack();

	pushToStack();
	TranslateRotateScale(glm::vec3(-4.0, 4.3f, 0.0f), 180.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(.2f, 0.8, 1.0f));
	uploadMatrixToShader();

	shapeGenerator.drawHalfHexagon();
	popFromStack();

	pushToStack();
	TranslateRotateScale(glm::vec3(0.0f, 4.6f, 4.0), 180.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.8, .2f));
	uploadMatrixToShader();

	shapeGenerator.drawHalfHexagon();
	popFromStack();

	//Triangle

	textureLoader.loadTexture(shaderProgram, Textures::GOLD);

	pushToStack();
	TranslateRotateScale(glm::vec3(0.0f, 3.0f, 5.0f), 90.f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.5, 0.5));
	uploadMatrixToShader();

	shapeGenerator.drawPyramid();
	popFromStack();







	
}

void TranslateRotateScale(glm::vec3 translation, float rotationAngle, glm::vec3 rotationAxis , glm::vec3 scaleRatio){
	modelMatrix = glm::translate(modelMatrix, translation);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationAngle), rotationAxis);
	modelMatrix = glm::scale(modelMatrix, scaleRatio);
}