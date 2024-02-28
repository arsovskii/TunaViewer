#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


Window::Window(unsigned int width, unsigned int height, std::string title)
{
	mWidth = width;
	mHeight = height;
	mWindowTitle = title;
	mWindow = NULL;
}

Window::~Window()
{
}


void Window::InitWindow()
{
	if (!InitGLFW())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return;
	}

	if (!CreateWindow())
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return;
	}

	if (!InitGlad())
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	RenderLoop();
	glfwTerminate();
}

bool Window::InitGLFW()
{
	if (!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return true;
}

bool Window::CreateWindow()
{
	mWindow = glfwCreateWindow(mWidth, mHeight, mWindowTitle.c_str(), nullptr, nullptr);
	if (mWindow == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(mWindow);

	glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
	{
		static_cast<Window*>(glfwGetWindowUserPointer(window))->window_size_callback(window, width, height);
	});

	return true;
}

bool Window::InitGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}

	return true;
}

void Window::RenderLoop()
{
	while (!glfwWindowShouldClose(mWindow))
	{
		ProcessInput();

		glClearColor(1.0f, 0.8431372549019608f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}

void Window::window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::ProcessInput()
{
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mWindow, true);
	}
}
