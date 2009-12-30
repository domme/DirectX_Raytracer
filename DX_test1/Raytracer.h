#pragma once
#include "D3D.h"

class Raytracer
{
public:
	Raytracer(void);
	Raytracer(HWND &hWnd, HINSTANCE &hInstance);
	
	~Raytracer(void);

	void trace(void);
	void render(void);


private:
	D3D d3d;
	HWND hWnd;
	HINSTANCE hInstance;
	ID3D10Texture2D* pTraceTexture;
	ID3D10Texture2D* pBackBufferTexture;
	D3D10_TEXTURE2D_DESC traceTexDesc;
	D3D10_BOX sourceRegion;

	void initTracing(void);
	

};
