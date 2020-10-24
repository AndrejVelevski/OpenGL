#pragma once

#include "GameObject.h"
#include "Shader.h"
#include "Camera.h"

struct Light
{
	enum Type
	{
		DirectionalLight, PointLight, SpotLight
	};

	Type type;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	glm::vec3 position;
	glm::vec3 direction;
	float innerCutoff;
	float outerCutoff;

	float range;
	float constant;
	float linear;
	float quadratic;

	inline Light()
	{
		type = PointLight;

		position = { 0.0f, 0.0f, 0.0f };
		direction = { 0.0f, -1.0f, 0.0f };
		innerCutoff = 10.0f;
		outerCutoff = 30.0f;

		ambient = { 0.2f, 0.2f, 0.2f };
		diffuse = { 1.0f, 1.0f, 1.0f };
		specular = { 1.0f, 1.0f, 1.0f };

		setRange(5.0f);
	}

	inline void setRange(float range)
	{
		this->range = range;
		constant = 1.0f;
		linear = 4.5f / range;
		quadratic = 75.5f / (range * range);
	}
};



