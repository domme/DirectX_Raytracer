#include "StdAfx.h"
#include "Raytracer.h"
#include "Camera.h"
#include <vector>
#include "Sphere.h"
#include "Light.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

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

	//Create camera for later use in the scene
	D3DXVECTOR3 camPosition = D3DXVECTOR3(0.0f, 0.0f,  -200.0f);
	D3DXVECTOR3 camLookAt = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 camUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Camera cam = *new Camera(&camPosition, &camLookAt, &camUp);
	
	//Create list of objects to appear in the scene
	vector<Mesh*> objectList;
	objectList.push_back(new Sphere(Material(D3DXCOLOR(255.0f, 0.0f, 0.0f, 255.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), .5f));

	//Create list of lights to luminate the scene
	vector<Light*> lightList;
	lightList.push_back(new Light());

	//and finally create the scene we're going to raytrace
	scene = *new Scene(objectList,lightList, cam);
}

std::wstring Raytracer::s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

Ray Raytracer::shootNewRay(int x, int y)
{
	float worldX, worldY;

	worldX = x;
	worldY = y;

	/*worldX = ((2.0f * x) / traceTexDesc.Width) - 1;
	worldY = -((2.0f * y) / traceTexDesc.Height) + 1;*/
	
	UINT numViewports = 1;

	
	D3D10_VIEWPORT viewport;
	d3d.pd3dDevice->RSGetViewports(&numViewports, &viewport);

	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);

	D3DXVECTOR3 v0;
	D3DXVec3Unproject(&v0, new D3DXVECTOR3(worldX, worldY, 0), &viewport, &scene.camera.projection, &scene.camera.view, &world);
	

	D3DXVECTOR3 v1;
	D3DXVec3Unproject(&v1, new D3DXVECTOR3(worldX, worldY, 1), &viewport, &scene.camera.projection, &scene.camera.view, &world);

	
	D3DXVECTOR3 rayDirection = v1 - v0;
	D3DXVECTOR3 normRayDir;
	D3DXVec3Normalize(&normRayDir, &rayDirection);

	
	/*stringstream s;
	s << "World Values: ";
	s << worldX;
	s << " ";
	s << worldY;
	s << endl;
	wstring ws = s2ws(s.str());
	OutputDebugString(reinterpret_cast<LPCWSTR>(ws.c_str()));*/
	//worldX = ((2.0f * x) / traceTexDesc.Width) - 1;
	//worldY = -((2.0f * y) / traceTexDesc.Height) + 1;

	return Ray(scene.camera.position, normRayDir);
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
			D3DXCOLOR tracedColor = scene.trace(shootNewRay(col, row));
			pTexels[rowStart + colStart + 0] = tracedColor.r; // Red
			pTexels[rowStart + colStart + 1] = tracedColor.g; // Green
			pTexels[rowStart + colStart + 2] = tracedColor.b;  // Blue
			pTexels[rowStart + colStart + 3] = 255;  // Alpha

			
		}
		
			/*string rowStartString = "rowStart: ";
			stringstream s;
			s << rowStartString;
			s << row;
			s << " ";
			s << endl;
			wstring rSS = s2ws(s.str());
			OutputDebugString(reinterpret_cast<LPCWSTR>(rSS.c_str()));*/
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




