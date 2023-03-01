#include "Program.h"

Program::Program()
{
    std::cout << "Creating Window\n";
    pWindow = new Window();

    std::cout << "Attaching Renderer\n";
    pRender = new Render(pWindow->GetWindow());

    // Game Loop
    bool isRunning = true;
    while (isRunning)
    {
        if (!pWindow->ProcessMessages())
        {
            std::cout << "Closing Window\n";
            isRunning = false;
        }

        pRender->RenderLoop();
    }
}

Program::~Program()
{
    delete pWindow;
    delete pRender;
}

