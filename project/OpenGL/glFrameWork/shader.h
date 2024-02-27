#pragma once

#include "core.h"

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void begin();//开始使用当前的shader
	void end();//结束使用当前的shader

private:
	enum class CheckType
	{
		NONE,
		COMPILE,
		LINK
	};
	void checkShaderErrors(GLuint, CheckType);

private:
	GLuint m_program{ 0 };
};
