#pragma once

#include <vector>
#include "Vertex.h"

class Buffer
{
private:
	unsigned int id;
	unsigned int type;

public:
	Buffer();
	Buffer(std::vector<Vertex>& data);
	Buffer(std::vector<unsigned int>& data);
	~Buffer();

	unsigned int getId();
	unsigned int getType();

	void create(std::vector<Vertex>& data);
	void create(std::vector<unsigned int>& data);
	void bind();
	void unbind();
};

