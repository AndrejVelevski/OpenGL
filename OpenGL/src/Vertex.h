#pragma once
#include <glm/glm.hpp>

struct Vertex
{
public:
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
	glm::ivec3 jointIds;
	glm::vec3 jointWeights;

	inline Vertex() {}

	inline Vertex(const glm::vec3& position, const glm::vec2& texCoord, const glm::vec3& normal, const glm::ivec3& jointIds = { 0,0,0 }, const glm::vec3& jointWeights = { 1,0,0 })
	{
		this->position = position;
		this->texCoord = texCoord;
		this->normal = normal;
		this->jointIds = jointIds;
		this->jointWeights = jointWeights;
	}
};