//	Ask the compiler to include minimal header files for our program.
#include "Win.h"
#include <d3d9.h>
#include <d3dx9.h>

//	use int main if you want to have a console to print out message

int main()

//	use WinMain if you don't want the console
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Win* gWin = gWin->getInstance();


	gWin->createWindow();
	//	Define Direct3D 9.
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	//	Define how the screen presents.
	D3DPRESENT_PARAMETERS d3dPP;
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = 400;
	d3dPP.BackBufferHeight = 300;
	d3dPP.hDeviceWindow = gWin->getHWND();

	IDirect3DDevice9* d3dDevice;
	//	Create a Direct3D 9 device.
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, gWin->getHWND(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);
	
	//	To Do: Cout out the message to indicate the failure.
	if (FAILED(hr)) {
		return 0;
	}

	LPDIRECT3DTEXTURE9 texture = NULL;
	LPD3DXSPRITE sprite = NULL;

	//	Create sprite. Study the documentation. 
	//HRESULT hr = D3DXCreateSprite(d3dDevice,&sprite);
	D3DXCreateSprite(d3dDevice, &sprite);

	D3DXCreateTextureFromFile(d3dDevice, L"img/bg1.png", &texture);

	bool executed = gWin->getIsFullscreen();
	int x = 0;
	int y = 0;
	while (gWin->gameLoop())//it just works
	{
		//	To Do:
		//	Update.
		
		if (executed != gWin->getIsFullscreen())//this is so that it gets executed once per toggle and not infinitely
		{
			if (gWin->getIsFullscreen())
			{
				d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
				d3dPP.Windowed = false;
				d3dDevice->Reset(&d3dPP);
			}
			else if (!gWin->getIsFullscreen())
			{
				d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
				d3dPP.Windowed = true;
				d3dDevice->Reset(&d3dPP);
			}

			executed = gWin->getIsFullscreen();
		}
		switch (gWin->keyPressed)
		{
		case VK_LEFT:
			x--;
			break;
		case VK_RIGHT:
			x++;
			break;
		case VK_UP:
			y--;
			break;
		case VK_DOWN:
			y++;
			break;
		default:
			break;
		}
		//	Clear the back buffer.
		d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(gWin->red, gWin->green, gWin->blue), 1.0f, 0);

		//	Begin the scene
		d3dDevice->BeginScene();
		//	To Do:
		//	Drawing.
		sprite->Begin(D3DXSPRITE_ALPHABLEND);

		sprite->Draw(texture, NULL, NULL, &D3DXVECTOR3(gWin->mouseX, gWin->mouseY, 0), D3DCOLOR_XRGB(255, 255, 255));
		

		//sprite->Draw(texture, NULL, NULL, &D3DXVECTOR3(x, y, 0), D3DCOLOR_XRGB(255, 255, 255));
		//sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		//sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		//sprite->Draw(texture, &spriteRect, NULL, &D3DXVECTOR3(32, 32, 0), D3DCOLOR_XRGB(255, 255, 255));

		//	End sprite drawing
		sprite->End();
		//	End the scene
		d3dDevice->EndScene();

		//	Present the back buffer to screen
		d3dDevice->Present(NULL, NULL, NULL, NULL);
	}

	

	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;

	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;

	return 0;
}



//--------------------------------------------------------------------