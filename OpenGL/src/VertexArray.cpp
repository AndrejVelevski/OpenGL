#include "VertexArray.h"
#include <glad\glad.h>
#include "Vertex.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
}

VertexArray::VertexArray(Buffer& vbo)
{
	glGenVertexArrays(1, &id);
	create(vbo);
}

VertexArray::VertexArray(Buffer& vbo, Buffer& ebo)
{
	glGenVertexArrays(1, &id);
	create(vbo, ebo);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

unsigned int VertexArray::getId()
{
	return id;
}

void VertexArray::create(Buffer& vbo)
{
	bind();
	vbo.bind();
	enable();
	unbind();

	vbo.unbind();
}

void VertexArray::create(Buffer& vbo, Buffer& ebo)
{
	bind();
	vbo.bind();
	ebo.bind();
	enable();
	unbind();

	vbo.unbind();
	ebo.unbind();
}

void VertexArray::bind()
{
	glBindVertexArray(id);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::enable()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glVertexAttribIPointer(3, 3, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, jointIds));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, jointWeights));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
}
