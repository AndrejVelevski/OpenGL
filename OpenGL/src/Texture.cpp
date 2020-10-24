#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad\glad.h>
#include <iostream>

Texture::Texture()
{
	glGenTextures(1, &id);
}

Texture::Texture(const std::string& source, int format, bool flipped)
{
	glGenTextures(1, &id);
	create(source, format, flipped);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

unsigned int Texture::getId()
{
	return id;
}

int Texture::getWidth()
{
	return width;
}
int Texture::getHeight()
{
	return height;
}

void Texture::create(const std::string& source, int format, bool flipped)
{
	this->flipped = flipped;
	stbi_set_flip_vertically_on_load(flipped);
	this->format = format;

	unsigned char* data = stbi_load(source.c_str(), &width, &height, &channels, 4);

	if (data)
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else
	{
		std::cerr << "Failed to load texture: " << source << std::endl;
	}
}

void Texture::bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}
