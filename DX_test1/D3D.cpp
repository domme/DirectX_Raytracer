#include "StdAfx.h"
#include "D3D.h"

D3D::D3D(void)
{
	pd3dDevice = NULL;
	pBackBuffer = NULL;
	pSwapChain = NULL;
}

HRESULT D3D::init(HWND &hWnd, HINSTANCE &hInstance)
{
	this->hWnd = hWnd;

	RECT window;

	GetClientRect(hWnd, &window);

	UINT width = window.right - window.left;
	UINT height = window.bottom - window.top;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory( &desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hWnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT hr = D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, D3D10_CREATE_DEVICE_DEBUG, D3D10_SDK_VERSION, &desc, &pSwapChain, &pd3dDevice);

	if(FAILED(hr))
	{
		MessageBox(hWnd, L"Device or SwapChain initialisation failed!", L"Initialisation error", MB_OK);
	}

	ID3D10Texture2D* lpBackBuffer;
	hr = pSwapChain->GetBuffer(0, __uuidof( ID3D10Texture2D ), ( LPVOID* ) &lpBackBuffer);
	if( FAILED(hr) )
		return hr;

	hr = pd3dDevice->CreateRenderTargetView( lpBackBuffer, NULL, &pBackBuffer);
	lpBackBuffer->Release();
	if(FAILED(hr))
		return hr;

	pd3dDevice->OMSetRenderTargets(1, &pBackBuffer, NULL);

	D3D10_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pd3dDevice->RSSetViewports(1, &vp);
}

void D3D::render(void)
{
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f};
	//pd3dDevice->ClearRenderTargetView(pBackBuffer, clearColor);

	pSwapChain->Present(0,0);
}

D3D::~D3D(void)
{
}