#pragma once
#include "Window.h"

class Application
{
public:
	Application();
	~Application();

	void startApp();

private:
	Window* mWindow;
};
