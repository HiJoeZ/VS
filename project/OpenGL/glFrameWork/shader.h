#pragma once

#include "core.h"

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void begin();//��ʼʹ�õ�ǰ��shader
	void end();//����ʹ�õ�ǰ��shader
	void setFloat(const std::string&, float);
	void setVec3(const std::string&, float, float, float);
	void setVec3(const std::string&, const float*);

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
