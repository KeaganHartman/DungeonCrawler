#pragma once
#include <iostream>
#include "Window.h"
#include "Render.h"

class Program
{
public:
	Program();
	~Program();

private:
	Window* pWindow;
	Render* pRender;
};

