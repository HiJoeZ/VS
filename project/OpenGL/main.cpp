#include <iostream>
#include "wrapper/checkError.h"
#include "application/Application.h"
#include "glFrameWork/core.h"
#include "glFrameWork/shader.h"

GLuint VAO = 0;
Shader* shader = nullptr;

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
    //创建一个vbo
    GLuint vbo = 0;
    GL_CALL(glGenBuffers(1, &vbo));

    //销毁一个vbo
    GL_CALL(glDeleteBuffers(1, &vbo));

    //创建n个vbo
    GLuint vboArr[] = { 0,0,0 };
    GL_CALL(glGenBuffers(3, vboArr));

    //销毁n个vbo
    GL_CALL(glDeleteBuffers(3, vboArr));
}

void prepareVAO()
{
    float positions[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    float colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    GLuint posVBO = 0;
    GL_CALL(glGenBuffers(1, &posVBO));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVBO));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    GLuint colorVBO = 0;
    GL_CALL(glGenBuffers(1, &colorVBO));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVBO));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

    GLuint EBO = 0;
    GL_CALL(glGenBuffers(1, &EBO));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GL_CALL(glGenVertexArrays(1, &VAO));
    GL_CALL(glBindVertexArray(VAO));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVBO));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVBO));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0));

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
    //生成一个vbo
    GLuint vbo = 0;
    GL_CALL(glGenBuffers(1, &vbo));

    //绑定当前vbo，到OpenGL状态机的当前vbo插槽上
    //GL_ARRAY_BUFFER表示当前vbo插槽
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));

    //向当前vbo传输数据，也是在开辟显存
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
}

void prepareSingleBuffer()
{
    //准备顶点位置数据与颜色数据
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

    //为位置与颜色数据各自生成一个vbo
    GLuint posVBO = 0;
    GLuint colorVBO = 0;
    GL_CALL(glGenBuffers(1, &posVBO));
    GL_CALL(glGenBuffers(1, &colorVBO));

    //给两个分开的vbo各自填充数据
    //填充position数据
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVBO));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
    //填充color数据
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVBO));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

    //生成VAO并绑定
    GLuint VAO = 0;
    GL_CALL(glGenVertexArrays(1, &VAO));
    GL_CALL(glBindVertexArray(VAO));

    //分别将位置/颜色属性的描述信息加入VAO当中
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVBO));//只有绑定了vbo下面的描述才会与此vbo相关
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVBO));//只有绑定了vbo下面的描述才会与此vbo相关
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

    GL_CALL(glBindVertexArray(0));//解绑VAO
}

void prepareInterleavedBuffer()
{
    //每行前三个数据为位置(x,y,z)，后三个数据为颜色(r,g,b)
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };

    GLuint pcVBO = 0;
    GL_CALL(glGenBuffers(1, &pcVBO));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, pcVBO));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    //生成VAO并绑定
    VAO = 0;
    GL_CALL(glGenVertexArrays(1, &VAO));
    GL_CALL(glBindVertexArray(VAO));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, pcVBO));//只有绑定了vbo下面的描述才会与此vbo相关
    //位置信息
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
    //颜色信息
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));

    GL_CALL(glBindVertexArray(0));//解绑VAO
}

void prepareVAOForGLTriangles()
{
    //准备顶点位置数据
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
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVBO));//只有绑定了vbo下面的描述才会与此vbo相关
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

    GL_CALL(glBindVertexArray(0));//解绑VAO
}

void prepareShader()
{
    shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void render()
{
    //画布清理
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

    //绑定当前program
    shader->begin();

    //绑定当前VAO
    GL_CALL(glBindVertexArray(VAO));

    //发出绘制指令
    //GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));
    //GL_CALL(glDrawArrays(GL_TRIANGLE_STRIP, 0, 6));
    //GL_CALL(glDrawArrays(GL_TRIANGLE_FAN, 0, 6));
    //GL_CALL(glDrawArrays(GL_LINES, 0, 6));
    //GL_CALL(glDrawArrays(GL_LINE_STRIP, 0, 6));

    GL_CALL(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));
    GL_CALL(glBindVertexArray(0));
    shader->end();
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