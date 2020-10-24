#pragma once

#include <glm/glm.hpp>
#include "GameObject.h"

class Camera : public GameObject
{
private:
	glm::mat4 projection;
	float near;
	float far;
	bool first;
	glm::vec2 mousePositionLast;

public:
	float fov;
	glm::vec3 target;
	glm::vec3 up;
	glm::vec3 front;
	glm::vec3 direction;

	bool lookAtTarget = false;

public:
	Camera();
	void create();

	glm::mat4 getView() const;
	glm::mat4 getProjection() const;

	void update(float delta);
};