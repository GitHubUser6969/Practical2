#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "resource.h"


class Win
{
private:

	static Win* instance;
	HWND g_hWnd;	
	WNDCLASS wndClass;
	bool isFullscreen;
	HINSTANCE hInstance;
	Win();

public:
	static int keyPressed;
	static int mouseX;
	static int mouseY;
	int red;
	int green;
	int blue;
	int speed;

	static Win* getInstance();
	void createWindow();
	void clearWindow();
	bool gameLoop();
	HWND getHWND();
	void setIsFullscreen(bool isFullScreen);
	bool getIsFullscreen();
	void ClientResize(HWND hWnd, int nWidth, int nHeight);

};

