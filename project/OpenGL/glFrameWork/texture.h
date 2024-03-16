#pragma once
#include "core.h"

class Texture
{
public:
	Texture(const std::string&, unsigned int);
	~Texture();

	void bind();

private:
	GLuint m_texture{ 0 };
	int m_width{ 0 };
	int m_height{ 0 };
	unsigned int m_unit{ 0 };
};
