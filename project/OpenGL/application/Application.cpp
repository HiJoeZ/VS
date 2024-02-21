#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

Application* Application::m_instance = nullptr;
Application* Application::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Application();
	}
	return m_instance;
}

Application::Application()
{
}

Application::~Application()
{
	delete m_window;
}

bool Application::init(const int& w, const int& h)
{
	m_width = w;
	m_height = h;
	//��ʼ��GLFW��������
	glfwInit();
	//����OpenGL���汾�š��ΰ汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//����OpenGL���ú���ģʽ����������Ⱦģʽ��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//
	m_window = glfwCreateWindow(m_width, m_height, "", NULL, NULL);
	if (m_window == nullptr) return false;
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glfwSetWindowUserPointer(m_window, this);

	glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallback);
	glfwSetKeyCallback(m_window, keyBoardCallback);

	return true;
}

bool Application::update()
{
	if (glfwWindowShouldClose(m_window)) return false;
	//���ַܷ�������Ϣ
	glfwPollEvents();
	//�л�˫����
	glfwSwapBuffers(m_window);
	return true;
}

void Application::destroy()
{
	glfwTerminate();
}

void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	std::cout << "onResizeCallback" << std::endl;
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self != nullptr)
	{
		self->m_ResizeCallBack(width, height);
	}
	//if (Application::getInstance()->m_ResizeCallBack != nullptr)
	//{
	//	Application::getInstance()->m_ResizeCallBack(width, height);
	//}
}

void Application::keyBoardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "onKeyBoardCallback" << std::endl;
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self != nullptr)
	{
		self->m_KeyBoardCallBack(key, action, mods);
	}
}
