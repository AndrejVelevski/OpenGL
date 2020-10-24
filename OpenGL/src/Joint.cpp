#include "Joint.h"
#include <glm\gtx\string_cast.hpp>

Joint::Joint(unsigned int id, const std::string& name, const glm::mat4& localTransform, const glm::mat4& inverseTransform, const glm::mat4& transform, Joint* parent)
{
	create(id, name, localTransform, inverseTransform, transform, parent);
}

void Joint::create(unsigned int id, const std::string& name, const glm::mat4& localTransform, const glm::mat4& inverseTransform, const glm::mat4& transform, Joint* parent)
{
	this->id = id;
	this->name = name;
	this->localTransform = localTransform;
	this->inverseTransform = inverseTransform;
	this->transform = transform;
	this->parent = parent;
}

unsigned int Joint::getId()
{
	return id;
}

glm::mat4 Joint::getLocalTransform()
{
	return localTransform;
}

glm::mat4 Joint::getInverseTransform()
{
	return inverseTransform;
}

std::string Joint::getName()
{
	return name;
}

void Joint::addChild(Joint* joint)
{
	children.push_back(joint);
}

std::ostream& operator<<(std::ostream& os, const Joint& j)
{
	/*if (j.parent == nullptr)
		os << "null";
	else
		os << (*j.parent).name;*/
	os << j.name << " " << j.id << std::endl;

	//os << glm::to_string(j.transform) << std::endl;

	for (int i = 0; i < j.children.size(); ++i)
	{
		os << *j.children[i];
	}

	return os;
}
