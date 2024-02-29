#pragma once
#include "Page.h"

class MainPage :
    public Page
{
public:
	MainPage(Window* window);
	~MainPage() override;
	void draw() override;

private:
	void openFileDialog();

	Window* mWindow;
};

