#include "shader.h"
#include "shader.h"
#include "shader.h"
#include "shader.h"
#include "shader.h"
#include "../wrapper/checkError.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        //打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        //将输入流输入到stringStream中
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        //关闭文件
        vShaderFile.close();
        fShaderFile.close();

        //将字符串读出来放到code string中
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (const std::ifstream::failure& err)
    {
        std::cout << "ERROR: Shader File Error: " << err.what() << std::endl;
    }

    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();
    //创建Shader程序（vs、fs)
    GLuint vertex, fragment;
    vertex = GL_CALL(glCreateShader(GL_VERTEX_SHADER));
    fragment = GL_CALL(glCreateShader(GL_FRAGMENT_SHADER));

    //为shader程序输入代码
    GL_CALL(glShaderSource(vertex, 1, &vertexShaderSource, NULL));
    GL_CALL(glShaderSource(fragment, 1, &fragmentShaderSource, NULL));

    int success = 0;
    char infoLog[1024];
    //执行shader代码编译
    GL_CALL(glCompileShader(vertex));
    //检查vertex编译结果
    checkShaderErrors(vertex, Shader::CheckType::COMPILE);

    GL_CALL(glCompileShader(fragment));
    //检查fragment编译结果
    checkShaderErrors(fragment, Shader::CheckType::COMPILE);

    //创建一个program壳子
    m_program = GL_CALL(glCreateProgram());

    //将vs与fs编译好的结果放到program壳子里
    GL_CALL(glAttachShader(m_program, vertex));
    GL_CALL(glAttachShader(m_program, fragment));

    //执行program的链接操作，生成可执行shader程序
    GL_CALL(glLinkProgram(m_program));

    //检查链接错误
    checkShaderErrors(m_program, Shader::CheckType::LINK);

    //清理链接完无用的shader
    GL_CALL(glDeleteShader(vertex));
    GL_CALL(glDeleteShader(fragment));
}

Shader::~Shader()
{
}

void Shader::begin()
{
    GL_CALL(glUseProgram(m_program));
}

void Shader::end()
{
    GL_CALL(glUseProgram(0));
}

void Shader::setFloat(const std::string& name, float value)
{
    GLuint location = GL_CALL(glGetUniformLocation(m_program,name.c_str()));

    GL_CALL(glUniform1f(location, value));
}

void Shader::setVec3(const std::string& name, float x, float y, float z)
{
    GLuint location = GL_CALL(glGetUniformLocation(m_program, name.c_str()));

    GL_CALL(glUniform3f(location, x, y, z));
}

void Shader::setVec3(const std::string& name, const float* values)
{
    GLuint location = GL_CALL(glGetUniformLocation(m_program, name.c_str()));

    GL_CALL(glUniform3fv(location, 1, values));
}

void Shader::checkShaderErrors(GLuint target, CheckType type)
{
    int success = 0;
    char infoLog[1024];

    switch(type)
    {
    case Shader::CheckType::NONE:
    {
        std::cout << "" << std::endl;
    }
        break;
    case Shader::CheckType::COMPILE:
    {
        GL_CALL(glGetShaderiv(target, GL_COMPILE_STATUS, &success));
        if (!success)
        {
            GL_CALL(glGetShaderInfoLog(target, 1024, NULL, infoLog));
            std::cout << "Error:Shader compile error\n" << infoLog << std::endl;
        }
    }
        break;
    case Shader::CheckType::LINK:
    {
        GL_CALL(glGetProgramiv(target, GL_LINK_STATUS, &success));
        if (!success)
        {
            GL_CALL(glGetProgramInfoLog(target, 1024, NULL, infoLog));
            std::cout << "Error:Shader link error\n" << infoLog << std::endl;
        }
    }
        break;
    default:
        break;
    }
}
