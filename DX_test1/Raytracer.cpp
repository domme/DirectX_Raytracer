#include "StdAfx.h"
#include "Raytracer.h"

Raytracer::Raytracer(void)
{
}

Raytracer::Raytracer(HWND &hWnd, HINSTANCE &hInstance)
{
	this->d3d = D3D();
	this->hWnd = hWnd;
	this->hInstance = hInstance;
	if(FAILED(d3d.init(hWnd, hInstance))) 
		MessageBox(hWnd, L"D3D init failed", L"FAILURE", MB_OK);
}

void Raytracer::trace(void)
{
	initTracing();

	D3D10_MAPPED_TEXTURE2D mappedTex;
	if(FAILED(pTraceTexture->Map(D3D10CalcSubresource(0, 0, 1), D3D10_MAP_WRITE_DISCARD, 0, &mappedTex)))
		MessageBox(hWnd, L"Texture Mapping Failed", L"Stupid Omme!", MB_OK);


	UCHAR* pTexels = (UCHAR*) mappedTex.pData;
	for(UINT row = 0; row < traceTexDesc.Height; row++)
	{
		UINT rowStart  = row * mappedTex.RowPitch;
		for(UINT col = 0; col < traceTexDesc.Width; col++)
		{
			UINT colStart = col * 4;
			pTexels[rowStart + colStart + 0] = 255; // Red
			pTexels[rowStart + colStart + 1] = 128; // Green
			pTexels[rowStart + colStart + 2] = 64;  // Blue
			pTexels[rowStart + colStart + 3] = 32;  // Alpha
		}
	}

	pTraceTexture->Unmap(D3D10CalcSubresource(0, 0, 1));

	//get a pointer to the BackBuffer as Texture2D
	
	if(FAILED(d3d.pSwapChain->GetBuffer(0, __uuidof( ID3D10Texture2D ), (LPVOID*) &pBackBufferTexture)))
		MessageBox(hWnd, L"BackBuffer could not be read", L"Oh nooooo", MB_OK);

	sourceRegion.left = 0;
	sourceRegion.top = 0;
	sourceRegion.right = traceTexDesc.Width;
	sourceRegion.bottom = traceTexDesc.Height;
	sourceRegion.front = 0;
	sourceRegion.back = 1;

	d3d.pd3dDevice->CopySubresourceRegion(pBackBufferTexture, 0, 0, 0, 0, pTraceTexture, 0, &sourceRegion);
//	d3d.pd3dDevice->CopyResource(pBackBufferTexture, pTraceTexture);

}

void Raytracer::initTracing(void)
{
	this->pTraceTexture = NULL;
	this->pBackBufferTexture = NULL;

	RECT rc;
	GetClientRect(hWnd, &rc);

	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	
	traceTexDesc.Width = width;
	traceTexDesc.Height = height;
	traceTexDesc.MipLevels = 1;
	traceTexDesc.ArraySize = 1;
	traceTexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	traceTexDesc.SampleDesc.Count = 1;
	traceTexDesc.SampleDesc.Quality = 0;
	traceTexDesc.MiscFlags = 0;
	traceTexDesc.Usage = D3D10_USAGE_DYNAMIC;
	traceTexDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
	traceTexDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	if(FAILED(d3d.pd3dDevice->CreateTexture2D(&traceTexDesc, NULL, &pTraceTexture)))
		MessageBox(hWnd, L"Failed to create Trace-Texture", L"ASSHOLE", MB_OK);
}

void Raytracer::render(void)
{

	this->d3d.render();
}

Raytracer::~Raytracer(void)
{
}




