#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Image.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>

#include "GUI/MainPage.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"

float aspectRatio = 1920.0 / 1080.0;


Window::Window(unsigned int width, unsigned int height, std::string title)
{
	mWidth = width;
	mHeight = height;
	mWindowTitle = title;
	mWindow = NULL;
	mGuiPage = NULL;
	mImage = NULL;
}

Window::~Window()
{
	delete mGuiPage;
}


void Window::initalize_gui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	io.DisplaySize.x = static_cast<float>(mWidth);
	io.DisplaySize.y = static_cast<float>(mHeight);
	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
	ImGui_ImplOpenGL3_Init("#version 150");

	printf("GUI init..");

	mGuiPage = new MainPage(this);
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
	printf("Created a window\n");

	initalize_gui();

	mImage = new Image("slika.jpg", mWindow);

	RenderLoop();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

bool Window::InitGLFW()
{
	if (!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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

void Window::render_gui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	mGuiPage->draw();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::RenderLoop()
{
	aspectRatio = mImage->getWidth() / mImage->getHeight();


	while (!glfwWindowShouldClose(mWindow))
	{
		ProcessInput();

		glClearColor(1.0f, 0.8431372549019608f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_SCISSOR_TEST);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_SCISSOR_TEST);


		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).


		mImage->drawImage();


		render_gui();


		glfwSwapInterval(1);
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}

void Window::window_size_callback(GLFWwindow* window, int width, int height)
{
	float desiredAspectRatio = aspectRatio;

	int widthOfViewport, heightOfViewport;
	int lowerLeftCornerOfViewportX = 0, lowerLeftCornerOfViewportY = 0; // Initialize these variables

	float requiredHeightOfViewport = width / desiredAspectRatio; // Corrected calculation

	if (requiredHeightOfViewport > height)
	{
		float requiredWidthOfViewport = height * desiredAspectRatio;
		if (requiredWidthOfViewport > width)
		{
			std::cout << "Error: Couldn't find dimensions that preserve the aspect ratio\n";
			widthOfViewport = width;
			heightOfViewport = height;
		}
		else
		{
			widthOfViewport = static_cast<int>(requiredWidthOfViewport);
			heightOfViewport = height;
			lowerLeftCornerOfViewportX = static_cast<int>((width - widthOfViewport) / 2.0f);
		}
	}
	else
	{
		widthOfViewport = width;
		heightOfViewport = static_cast<int>(requiredHeightOfViewport);
		lowerLeftCornerOfViewportY = static_cast<int>((height - heightOfViewport) / 2.0f);
	}

	glViewport(lowerLeftCornerOfViewportX, lowerLeftCornerOfViewportY, widthOfViewport, heightOfViewport);
}


void Window::ProcessInput()
{
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mWindow, true);
	}
}

void Window::changeImage(std::string path)
{
	if(mImage != nullptr)
	{
		delete mImage;
	}

	mImage = new Image(path, mWindow);
}
