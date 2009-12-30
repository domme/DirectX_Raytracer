#pragma once
#include "D3D10.h"
#include "D3DX10.h"


class D3D
{
public:
	D3D(void);
	~D3D(void);

	ID3D10Device*				pd3dDevice;
	ID3D10RenderTargetView*		pBackBuffer;
	IDXGISwapChain*				pSwapChain;

	HRESULT init(HWND &hWnd, HINSTANCE &hInstance);
	void render(void);

private: 
	HWND hWnd;
	
};
