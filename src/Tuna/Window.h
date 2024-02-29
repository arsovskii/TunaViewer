#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>


#include "GUI/Page.h"
#include "imgui/imgui.h"

class Image;

class Window
{
public:
	Window(unsigned int width, unsigned int height, std::string title);
	~Window();
	void initalize_gui();

	void InitWindow();

	ImGuiIO getIO()
	{
		return io;
	}

	void changeImage(std::string path);
private:
	Image* mImage;
	Page* mGuiPage;

	unsigned int mWidth;
	unsigned int mHeight;
	std::string mWindowTitle;
	GLFWwindow* mWindow;
	ImGuiIO io;


	bool InitGLFW();
	bool CreateWindow();
	bool InitGlad();
	void RenderLoop();
	void window_size_callback(GLFWwindow* window, int width, int height);
	void ProcessInput();
	void render_gui(); //todo:refactor na imina
};

#endif
