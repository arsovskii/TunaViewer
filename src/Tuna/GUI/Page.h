#pragma once


class Window;

class Page
{
public:
	virtual ~Page()
	{
		
	}

	virtual void draw() = 0;
};
