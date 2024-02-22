#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "wrapper/checkError.h"
#include "application/Application.h"

GLuint program = 0, VAO = 0;

void onResize(int w, int h)
{
    std::cout << "onResize" << std::endl;
    GL_CALL(glViewport(0, 0, w, h));
}

void onKeyBoard(int key, int action, int mods)
{
    std::cout << key << std::endl;
}

void prepareVBO()
{
    //����һ��vbo
    GLuint vbo = 0;
    GL_CALL(glGenBuffers(1, &vbo));

    //����һ��vbo
    GL_CALL(glDeleteBuffers(1, &vbo));

    //����n��vbo
    GLuint vboArr[] = { 0,0,0 };
    GL_CALL(glGenBuffers(3, vboArr));

    //����n��vbo
    GL_CALL(glDeleteBuffers(3, vboArr));
}

void prepareVAO()
{
    float positions[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 1, 3
    };

    GLuint posVBO = 0;
    GL_CALL(glGenBuffers(1, &posVBO));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVBO));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    GLuint EBO = 0;
    GL_CALL(glGenBuffers(1, &EBO));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GL_CALL(glGenVertexArrays(1, &VAO));
    GL_CALL(glBindVertexArray(VAO));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVBO));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));

    GL_CALL(glBindVertexArray(0));
}

void prepare()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };
    //����һ��vbo
    GLuint vbo = 0;
    GL_CALL(glGenBuffers(1, &vbo));

    //�󶨵�ǰvbo����OpenGL״̬���ĵ�ǰvbo�����
    //GL_ARRAY_BUFFER��ʾ��ǰvbo���
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));

    //��ǰvbo�������ݣ�Ҳ���ڿ����Դ�
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
}

void prepareSingleBuffer()
{
    //׼������λ����������ɫ����
    float positions[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    float colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };

    //Ϊλ������ɫ���ݸ�������һ��vbo
    GLuint posVBO = 0;
    GLuint colorVBO = 0;
    GL_CALL(glGenBuffers(1, &posVBO));
    GL_CALL(glGenBuffers(1, &colorVBO));

    //�������ֿ���vbo�����������
    //���position����
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVBO));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
    //���color����
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVBO));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

    //����VAO����
    GLuint VAO = 0;
    GL_CALL(glGenVertexArrays(1, &VAO));
    GL_CALL(glBindVertexArray(VAO));

    //�ֱ�λ��/��ɫ���Ե�������Ϣ����VAO����
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVBO));//ֻ�а���vbo����������Ż����vbo���
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVBO));//ֻ�а���vbo����������Ż����vbo���
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

    GL_CALL(glBindVertexArray(0));//���VAO
}

void prepareInterleavedBuffer()
{
    //ÿ��ǰ��������Ϊλ��(x,y,z)������������Ϊ��ɫ(r,g,b)
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };

    GLuint pcVBO = 0;
    GL_CALL(glGenBuffers(1, &pcVBO));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, pcVBO));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    //����VAO����
    VAO = 0;
    GL_CALL(glGenVertexArrays(1, &VAO));
    GL_CALL(glBindVertexArray(VAO));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, pcVBO));//ֻ�а���vbo����������Ż����vbo���
    //λ����Ϣ
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
    //��ɫ��Ϣ
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));

    GL_CALL(glBindVertexArray(0));//���VAO
}

void prepareVAOForGLTriangles()
{
    //׼������λ������
    float positions[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.8f,  0.8f, 0.0f,
         0.8f,  0.0f, 0.0f
    };

    //
    GLuint posVBO = 0;
    GL_CALL(glGenBuffers(1, &posVBO));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVBO));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    //
    GL_CALL(glGenVertexArrays(1, &VAO));
    GL_CALL(glBindVertexArray(VAO));

    //
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVBO));//ֻ�а���vbo����������Ż����vbo���
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

    GL_CALL(glBindVertexArray(0));//���VAO
}

void prepareShader()
{
    //��дvs��fs��Դ�����ַ���
    const char* vertexShaderSource =
        "#version 460 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    //����Shader����vs��fs)
    GLuint vertex, fragment;
    vertex = GL_CALL(glCreateShader(GL_VERTEX_SHADER));
    fragment = GL_CALL(glCreateShader(GL_FRAGMENT_SHADER));

    //Ϊshader�����������
    GL_CALL(glShaderSource(vertex, 1, &vertexShaderSource, NULL));
    GL_CALL(glShaderSource(fragment, 1, &fragmentShaderSource, NULL));

    int success = 0;
    char infoLog[1024];
    //ִ��shader�������
    GL_CALL(glCompileShader(vertex));
    //���vertex������
    GL_CALL(glGetShaderiv(vertex, GL_COMPILE_STATUS, &success));
    if (!success)
    {
        GL_CALL(glGetShaderInfoLog(vertex, 1024, NULL, infoLog));
        std::cout << "Error:Shader compile error --vertex\n" << infoLog << std::endl;
    }

    GL_CALL(glCompileShader(fragment));
    //���fragment������
    GL_CALL(glGetShaderiv(fragment, GL_COMPILE_STATUS, &success));
    if (!success)
    {
        GL_CALL(glGetShaderInfoLog(fragment, 1024, NULL, infoLog));
        std::cout << "Error:Shader compile error --fragment\n" << infoLog << std::endl;
    }

    //����һ��program����
    program = GL_CALL(glCreateProgram());

    //��vs��fs����õĽ���ŵ�program������
    GL_CALL(glAttachShader(program, vertex));
    GL_CALL(glAttachShader(program, fragment));

    //ִ��program�����Ӳ��������ɿ�ִ��shader����
    GL_CALL(glLinkProgram(program));

    //������Ӵ���
    GL_CALL(glGetProgramiv(program, GL_LINK_STATUS, &success));
    if (!success)
    {
        GL_CALL(glGetProgramInfoLog(program, 1024, NULL, infoLog));
        std::cout << "Error:Shader link error\n" << infoLog << std::endl;
    }

    //�������������õ�shader
    GL_CALL(glDeleteShader(vertex));
    GL_CALL(glDeleteShader(fragment));
}

void render()
{
    //��������
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

    //�󶨵�ǰprogram
    GL_CALL(glUseProgram(program));

    //�󶨵�ǰVAO
    GL_CALL(glBindVertexArray(VAO));

    //��������ָ��
    //GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));
    //GL_CALL(glDrawArrays(GL_TRIANGLE_STRIP, 0, 6));
    //GL_CALL(glDrawArrays(GL_TRIANGLE_FAN, 0, 6));
    //GL_CALL(glDrawArrays(GL_LINES, 0, 6));
    //GL_CALL(glDrawArrays(GL_LINE_STRIP, 0, 6));

    GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}

int main()
{
    if (!mApp->init(800, 600)) return -1;
    mApp->setResizeCallBack(onResize);
    mApp->setKeyBoardCallBack(onKeyBoard);

    GL_CALL(glViewport(0,0,800,600));
    GL_CALL(glClearColor(0.2f,0.3f,0.3f,1.0f));

    prepareShader();
    //prepare();
    //prepareSingleBuffer();
    //prepareInterleavedBuffer();
    //prepareVAOForGLTriangles();
    prepareVAO();

    while (mApp->update())
    {
        render();
    }

    mApp->destroy();
    return 0;
}