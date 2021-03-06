#include "Win.h"

Win* Win::instance = 0;
int Win::keyPressed = 0;
int Win::mouseX = 0;
int Win::mouseY = 0;

Win* Win::getInstance()
{
	if (!instance)
	{
		instance = new Win;
	}

	return instance;
}

Win::Win()
{	
	this->red = 0;
	this->green = 0;
	this->blue = 0;
	this->speed = 1;
	this->isFullscreen = false;
	this->hInstance = GetModuleHandle(NULL);
	this->g_hWnd = NULL;
}



//	Window Procedure, for event handling
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	Win* gWin = gWin->getInstance();

	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		//std::cout << wParam << std::endl;
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			break;
		}
		//else if (wParam == 70)
		//{
		//	
		//	if (!gWin->getIsFullscreen())
		//	{
		//		gWin->setIsFullscreen(true);
		//	}
		//	else if(gWin->getIsFullscreen())
		//	{
		//		gWin->setIsFullscreen(false);
		//	}
		//}
		//else if (wParam == 82 || wParam == 71 || wParam == 66 || wParam == 38 || wParam == 40)
		//{
		//	if (wParam == 82)
		//	{
		//		
		//		gWin->red += gWin->speed;
		//		if (gWin->red > 256)
		//		{
		//			gWin->red = 0;
		//		}
		//	}
		//	else if (wParam == 71)
		//	{
		//		gWin->green += gWin->speed;
		//		if (gWin->green > 256)
		//		{
		//			gWin->green = 0;
		//		}
		//	}
		//	else if (wParam == 66)
		//	{
		//		gWin->blue += gWin->speed;
		//		if (gWin->blue > 256)
		//		{
		//			gWin->blue = 0;
		//		}
		//	}
		//	else if (wParam == 38)
		//	{
		//		if (!(gWin->speed >= 10))
		//		{
		//			gWin->speed += 1;
		//		}
		//	}
		//	else if (wParam == 40)
		//	{
		//		if (!(gWin->speed <= 1))
		//		{
		//			gWin->speed -= 1;
		//		}
		//	}
		//	

		//	std::cout  << "Red   : " << (int)gWin->red 
		//		<< std::endl << "Green : " << (int)gWin->green
		//		<< std::endl << "Blue  : " << (int)gWin->blue 
		//		<< std::endl << "Speed :  " << gWin->speed << std::endl;
		//	std::cout << "Press F for Fullscreen" << std::endl;
		//}

		gWin->keyPressed = wParam;


	case WM_KEYUP:
		gWin->keyPressed = 0;
		break;
	case WM_MOUSEMOVE:
		gWin->mouseX = LOWORD(lParam);
		gWin->mouseY = HIWORD(lParam);
		break;
		//	Default handling for other messages.
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Win::createWindow()
{
	/*
	Step 1
	Define and Register a Window.
*/

//	Sset all members in wndClass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));

	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACKONWHITE);
	wndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1)); //RIN_CURSOR
	//wndClass.hCursor = LoadCursorFromFile(AOT);
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	wndClass.hInstance = hInstance;	//	GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = L"My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	//	Register the window.
	RegisterClass(&wndClass);

	/*
		Step 2
		Create the Window.
	*/
	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, TEXT("Yeager"), WS_OVERLAPPEDWINDOW, 0, 100, 416, 339, g_hWnd, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);


	//RECT rcClient, rcWind;
	//GetClientRect(g_hWnd, &rcClient);
	//GetWindowRect(g_hWnd, &rcWind);

	//int x = (rcWind.right - rcWind.left) - rcClient.right;
	//int y = (rcWind.bottom - rcWind.top) - rcClient.bottom;

	//std::cout << x << std::endl;
	//std::cout << y << std::endl;
	//	Some interesting function to try out.
		//ShowCursor(false);

}



void Win::clearWindow()
{
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, hInstance);
}

bool Win::gameLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	/*
		Step 3
		Handling window messages
		NOTE! There are several ways of writing the message loop.
		You have to based on which kind of application your are writing.
	*/

	/*
		The if- version process one message per one iteration loop
		The while- version will clear the message queue before dealing with your own code.

		Another function is GetMessage.
		This function is not suitable for game, because it will block your program until it recieves a message.
		your code will only executed when you have messages, otherwies your pogram will be waiting... (similar to cin)
		Suitable for event based program, such as bussiness app.
	*/
	//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT)
		{
			break;
		}
		
		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);
		
	}

	/*
		Write your code here...
	*/


	return msg.message != WM_QUIT;
}

HWND Win::getHWND()
{
	return this->g_hWnd;
}


void Win::setIsFullscreen(bool T)
{
	isFullscreen = T;
}

bool Win::getIsFullscreen()
{
	return this->isFullscreen;
}


void Win::ClientResize(HWND hWnd, int nWidth, int nHeight)
{
	RECT rcClient, rcWind;
	POINT ptDiff;
	GetClientRect(hWnd, &rcClient);
	GetWindowRect(hWnd, &rcWind);
	ptDiff.x = (rcWind.right - rcWind.left) - rcClient.right;
	ptDiff.y = (rcWind.bottom - rcWind.top) - rcClient.bottom;
	MoveWindow(hWnd, rcWind.left, rcWind.top, nWidth + ptDiff.x, nHeight + ptDiff.y, TRUE);
}
