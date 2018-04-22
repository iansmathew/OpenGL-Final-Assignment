#pragma once

void display();

void timer(int id);

void init();

void initCamera();

void initLights();

void uploadMatrixToShader();

void pushToStack();

void popFromStack();

void mouseMoveEvent(int x, int y);

void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);

void controlCamera();

void drawDemoShapes();

void TranslateRotateScale(glm::vec3 translation, float rotationAngle, glm::vec3 rotationAxis, glm::vec3 scaleRatio);