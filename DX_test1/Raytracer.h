#pragma once
#include "D3D.h"
#include "Scene.h"
#include "Ray.h"

class Raytracer
{
public:
	Raytracer(void);
	Raytracer(HWND &hWnd, HINSTANCE &hInstance);
	
	~Raytracer(void);

	void trace(void);
	void render(void);


private:

	std::wstring s2ws( const std::string &s);
	Scene scene;
	D3D d3d;
	HWND hWnd;
	HINSTANCE hInstance;
	ID3D10Texture2D* pTraceTexture;
	ID3D10Texture2D* pBackBufferTexture;
	D3D10_TEXTURE2D_DESC traceTexDesc;
	D3D10_BOX sourceRegion;

	void initTracing(void);
	Ray* shootNewRay(int x, int y);
	

};
