#include "Buffer.h"
#include <glad\glad.h>

Buffer::Buffer()
{
	glGenBuffers(1, &id);
}

Buffer::Buffer(std::vector<Vertex>& data)
{
	glGenBuffers(1, &id);
	create(data);
}

Buffer::Buffer(std::vector<unsigned int>& data)
{
	glGenBuffers(1, &id);
	create(data);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &id);
}

unsigned int Buffer::getId()
{
	return id;
}

unsigned int Buffer::getType()
{
	return type;
}

void Buffer::create(std::vector<Vertex>& data)
{
	type = GL_ARRAY_BUFFER;
	bind();
	glBufferData(type, data.size() * sizeof(Vertex), &data[0], GL_STATIC_DRAW);
	unbind();
}

void Buffer::create(std::vector<unsigned int>& data)
{
	type = GL_ELEMENT_ARRAY_BUFFER;
	bind();
	glBufferData(type, data.size() * sizeof(unsigned int), &data[0], GL_STATIC_DRAW);
	unbind();
}

void Buffer::bind()
{
	glBindBuffer(type, id);
}

void Buffer::unbind()
{
	glBindBuffer(type, 0);
}
