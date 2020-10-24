#include "Camera.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

unsigned int width;
unsigned int height;

Camera::Camera()
{
	create();
}

void Camera::create()
{
	target = { 0, 0, 0 };
	up = { 0, 1, 0 };
	front = { 0, 0, -1 };
	direction = { 0, 0, 0 };

	fov = 70.0;
	near = 0.01;
	far = 1000.0;

	projection = glm::perspective(glm::radians(fov), (float)width / (float)height, near, far);

	rotation.y = -90;
	first = true;
}

glm::mat4 Camera::getView() const
{
	if (lookAtTarget)
		return glm::lookAt(position, target, up);
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjection() const
{
	return projection;
}

void Camera::update(float delta)
{
	if (first)
	{
		first = false;
		mousePositionLast.x = Input::mousex();
		mousePositionLast.y = Input::mousey();
		return;
	}
	projection = glm::perspective(glm::radians(fov), (float)width / (float)height, near, far);

	float xoffset = Input::mousex() - mousePositionLast.x;
	float yoffset = Input::mousey() - mousePositionLast.y;
	mousePositionLast = { Input::mousex(), Input::mousey() };

	float sensitivity = 0.1;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	rotation.y += xoffset;
	rotation.x += yoffset;

	if (rotation.x > 89.0f)
		rotation.x = 89.0f;
	if (rotation.x < -89.0f)
		rotation.x = -89.0f;

	direction.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	direction.y = -sin(glm::radians(rotation.x));
	direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	front = glm::normalize(direction);
}
