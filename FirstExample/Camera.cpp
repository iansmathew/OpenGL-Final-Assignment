#include "Camera.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

Camera::Camera()
	: cameraPos(0.0f, 0.0f, 9.0f)
	, cameraViewDir(0.0f, 0.0f, -1.0f)
	, UP_DIR(0.0f, 1.0f, 0.0)
{
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(cameraPos, cameraPos + cameraViewDir, UP_DIR);
}

void Camera::mouseUpdate(const glm::vec2 & newMousePosition)
{
	glm::vec2 mouseDelta = newMousePosition - oldMousePos;
	
	if (glm::length(mouseDelta) > 50) //if too big a jump, forget about it.
	{
		oldMousePos = newMousePosition;
		return;
	}

	cameraViewDir = glm::rotate(cameraViewDir, mouseDelta.x * -0.001f, UP_DIR);

	//Vertical rotation
	glm::vec3 rightVec = glm::cross(cameraViewDir, UP_DIR);
	cameraViewDir = glm::rotate(cameraViewDir, mouseDelta.y * -0.001f, rightVec);


	oldMousePos = newMousePosition;
}

void Camera::movePosition(glm::vec3 mouseDelta)
{
	cameraPos += mouseDelta;
}

void Camera::moveForward()
{
	cameraPos += MOVEMENT_SPEED * cameraViewDir;
}

void Camera::moveBack()
{
	cameraPos -= MOVEMENT_SPEED * cameraViewDir;
}

void Camera::strafeLeft()
{
	glm::vec3 rightVec = glm::cross(cameraViewDir, UP_DIR);
	cameraPos += MOVEMENT_SPEED * rightVec;

}

void Camera::strafeRight()
{
	glm::vec3 rightVec = glm::cross(cameraViewDir, UP_DIR);
	cameraPos -= MOVEMENT_SPEED * rightVec;

}


