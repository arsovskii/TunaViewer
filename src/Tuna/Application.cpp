#include "Application.h"


Application::Application()
{
	mWindow = new Window(860, 640, "TunaViewer");
}

Application::~Application()
{
	delete mWindow;
}

void Application::startApp()
{
	mWindow->InitWindow();
}
