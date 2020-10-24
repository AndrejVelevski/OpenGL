#include "GameObject.h"
#include <glm/gtc/type_ptr.hpp>

glm::mat4 GameObject::getTransform() const
{
	glm::mat4 transform = glm::mat4(1.0f);

	transform = glm::translate(transform, position);
	transform = glm::scale(transform, scale);
	transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
	transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
	transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));

	return transform;
}
