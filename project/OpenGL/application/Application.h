#pragma once

#define mApp Application::getInstance()

using ResizeCallBack = void(*)(int, int);
using KeyBoardCallBack = void(*)(int, int, int);

class GLFWwindow;
class Application
{
public:
	~Application();
	static Application* getInstance();

	bool init(const int& w = 800, const int& h = 600);
	bool update();
	void destroy();

	unsigned int getWidth()const { return m_width; }
	unsigned int getHeight()const { return m_height; }

	void setResizeCallBack(ResizeCallBack callback) { m_ResizeCallBack = callback; }
	void setKeyBoardCallBack(KeyBoardCallBack callback) { m_KeyBoardCallBack = callback; }

private:
	explicit Application();
	static void frameBufferSizeCallback(GLFWwindow*, int, int);
	static void keyBoardCallback(GLFWwindow*, int, int, int, int);

private:
	static Application* m_instance;
	unsigned int m_width{ 0 };
	unsigned int m_height{ 0 };
	GLFWwindow* m_window{ nullptr };
	ResizeCallBack m_ResizeCallBack{ nullptr };
	KeyBoardCallBack m_KeyBoardCallBack{ nullptr };
};
