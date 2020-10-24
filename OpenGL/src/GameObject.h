#pragma once

#include <glm/glm.hpp>
class GameObject
{
public:
	glm::vec3 position = {0, 0, 0};
	glm::vec3 rotation = {0, 0, 0};
	glm::vec3 scale = {1, 1, 1};

	virtual glm::mat4 getTransform() const;
};