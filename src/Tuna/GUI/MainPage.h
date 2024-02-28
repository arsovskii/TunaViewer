#pragma once
#include "Page.h"

class MainPage :
    public Page
{
public:
	MainPage();
	~MainPage() override;
	void draw(Window* window) override;
};

