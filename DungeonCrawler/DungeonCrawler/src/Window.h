#pragma once
#include <Windows.h>


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	// Constructor
	Window();
		
	
	// Delete Copy Constructor and "=" operator
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	// Deconstructor
	~Window();

	bool ProcessMessages();

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
};

