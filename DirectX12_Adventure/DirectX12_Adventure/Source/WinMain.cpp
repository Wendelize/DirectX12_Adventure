#pragma region Includes
#include "PreCompiledHeaders.h"
#pragma endregion

///////////////////////////////////////////////////
// GLOBAL VARIABLES
///////////////////////////////////////////////////
#pragma region GlobalVariables

WCHAR WindowClass[MAX_NAME_SIZE];
WCHAR WindowTitle[MAX_NAME_SIZE];
INT WindowWidth;
INT WindowHeight;
HICON hIcon;
#pragma endregion


///////////////////////////////////////////////////
// FUNCTION DECLARATIONS
///////////////////////////////////////////////////
#pragma region FunctionDeclerations

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);
VOID InitializeVariables();
VOID CreateWindowClass();
VOID InitializeWindow();
VOID MessageLoop();
#pragma endregion


///////////////////////////////////////////////////
// MAIN LOOP
///////////////////////////////////////////////////
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	InitializeVariables();
	CreateWindowClass();
	InitializeWindow();
	MessageLoop();
	
	return 0;
}

////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////
#pragma region Functions

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg) {
		// DESTROY WINDOW
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wparam, lparam);
}

VOID InitializeVariables() 
{
	// Init Global Variables
	LoadString(HInstance(), IDS_GAMENAME, WindowTitle, MAX_NAME_SIZE);
	LoadString(HInstance(), IDS_WINDOWCLASS, WindowClass, MAX_NAME_SIZE);

	WindowWidth = 1200;
	WindowHeight = 800;
	hIcon = LoadIcon(HInstance(), MAKEINTRESOURCE(IDI_MAINICON));
}

VOID CreateWindowClass() 
{
	// Create a Window Class
	WNDCLASSEX window;

	window.cbSize = sizeof(WNDCLASSEX);
	window.style = CS_HREDRAW | CS_VREDRAW; // Horizontal/Vertical EDraw
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.hCursor = LoadCursor(nullptr, IDC_ARROW);
	window.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	window.hIcon = hIcon;
	window.hIconSm = hIcon;
	window.lpszClassName = WindowClass;
	window.lpszMenuName = nullptr;
	window.hInstance = HInstance();
	window.lpfnWndProc = WindowProcess;

	RegisterClassEx(&window);
}

VOID InitializeWindow() 
{
	// Init and Display Window
	HWND hWnd = CreateWindow(
		WindowClass,
		WindowTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		WindowWidth,
		WindowHeight,
		nullptr,			// Parent Window
		nullptr,			// Menu
		HInstance(),
		nullptr);			// Something about taking instructions 

	if (!hWnd)
	{
		// WINDOW ERROR
		MessageBox(0, L"Failed to create window!", 0, 0);
		PostQuitMessage(0);
	}

	ShowWindow(hWnd, SW_SHOW);
}

VOID MessageLoop()
{
	// Listen for Message events 
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		// Process potential Window messages
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Add Game-Loop
	}
}

#pragma endregion