#pragma once
#include "Buffer.h"

class VertexArray
{
private:
	unsigned int id;

public:
	VertexArray();
	VertexArray(Buffer& vbo);
	VertexArray(Buffer& vbo, Buffer& ebo);
	~VertexArray();

	unsigned int getId();

	void create(Buffer& vbo);
	void create(Buffer& vbo, Buffer& ebo);
	void bind();
	void unbind();
	void enable();
};