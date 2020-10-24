#pragma once
#include <string>

class Texture
{
private:
	unsigned int id;
	int width;
	int height;
	int channels;
	bool flipped;
	int format;

public:
	Texture();
	Texture(const std::string& source, int format, bool flipped = true);
	~Texture();

	unsigned int getId();
	int getWidth();
	int getHeight();

	void create(const std::string& source, int format, bool flipped = true);
	void bind(unsigned int slot=0);
};

