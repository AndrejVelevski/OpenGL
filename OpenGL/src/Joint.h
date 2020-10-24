#pragma once

#include "glm/glm.hpp"
#include <vector>
#include <string>
#include <ostream>

class Joint
{
private:
	unsigned int id;
	std::string name;
	glm::mat4 localTransform;
	glm::mat4 inverseTransform;

public:
	glm::mat4 transform;
	std::vector<Joint*> children;
	Joint* parent;

public:
	Joint(unsigned int id, const std::string& name, const glm::mat4& localTransform, const glm::mat4& inverseTransform, const glm::mat4& transform, Joint* parent);

	void create(unsigned int id, const std::string& name, const glm::mat4& localTransform, const glm::mat4& inverseTransform, const glm::mat4& transform, Joint* parent);

	unsigned int getId();
	glm::mat4 getLocalTransform();
	glm::mat4 getInverseTransform();
	std::string getName();
	void addChild(Joint* joint);

	friend std::ostream& operator<<(std::ostream& os, const Joint& j);
	
};