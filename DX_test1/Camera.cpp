#include "StdAfx.h"
#include "Camera.h"


Camera::Camera(void)
{
}

Camera::Camera(D3DXVECTOR3* position,D3DXVECTOR3* poi, D3DXVECTOR3* up)
{
	this->view = *new D3DXMATRIX();
	D3DXMatrixIdentity(&view);

	this->projection = *new D3DXMATRIX();
	D3DXMatrixIdentity(&projection);
	
	this->position = *position;
	D3DXMatrixLookAtLH(&view, position, poi, up);
	//D3DXMatrixIdentity(&projection);
	//D3DXMatrixOrthoLH(&projection, 800.0f, 600.0f, 0.1f, 10000.0f);
	D3DXMatrixPerspectiveFovLH(&projection, 3.14159f/4.0f , 1.3333f, 0.1f, 10000.0f);
}

Camera::~Camera(void)
{
}
