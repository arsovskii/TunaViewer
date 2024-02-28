#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Window
{
public:
	Window(unsigned int width, unsigned int height, std::string title);
	~Window();

	void InitWindow();

private:
	unsigned int mWidth;
	unsigned int mHeight;
	std::string mWindowTitle;
	GLFWwindow* mWindow;

	bool InitGLFW();
	bool CreateWindow();
	bool InitGlad();
	void RenderLoop();
	void window_size_callback(GLFWwindow* window, int width, int height);
	void ProcessInput();
};

#endif
