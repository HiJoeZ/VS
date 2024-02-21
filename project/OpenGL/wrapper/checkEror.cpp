#include "checkError.h"
#include <iostream>
#include <glad/glad.h>
#include <assert.h>

void checkError()
{
    GLenum errorCode = glGetError();
    std::string errString = "";
    if (errorCode != GL_NO_ERROR)
    {
        switch (errorCode)
        {
        case GL_INVALID_ENUM:
            errString = "INVALID_ENUM";
            break;

        case GL_INVALID_VALUE:
            errString = "INVALID_VALUE";
            break;

        case GL_INVALID_OPERATION:
            errString = "INVALID_OPERATION";
            break;

        case GL_OUT_OF_MEMORY:
            errString = "OUT_OF_MEMORY";
            break;
        default:
            errString = "UNKNOW";
            break;
        }
        std::cout << errString << std::endl;
        assert(false);
    }
}
