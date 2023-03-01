#include <iostream>
#include "Window.h"
#include "Render.h"

int main()
{
	std::cout << "Creating Window\n";

	Window* pWindow = new Window();
	Render* pRender = new Render(pWindow->GetWindow());

	bool running = true;
	while (running)
	{
		if (!pWindow->ProcessMessages())
		{
			std::cout << "Closing Window\n";
			running = false;
		}
			

		// Render
		pRender->RenderLoop();
		Sleep(10);
	}

	delete pRender;
	delete pWindow;

	return 0;
}