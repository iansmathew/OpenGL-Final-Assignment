#pragma once
#include <glm/glm.hpp>

class Camera
{
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraViewDir;
	const glm::vec3 UP_DIR;

	glm::vec2 oldMousePos;

	const float MOVEMENT_SPEED = 0.1f;

public:
	Camera();
	glm::mat4 getViewMatrix() const;
	void mouseUpdate(const glm::vec2& newMousePosition);
	void movePosition(glm::vec3 mouseDelta);

	void moveForward();
	void moveBack();
	void strafeLeft();
	void strafeRight();

	glm::vec3 getCameraPosition() const { return cameraPos; }

};

