#include "StdAfx.h"
#include "Camera.h"

Camera::Camera(void)
{
}

Camera::Camera(D3DXVECTOR3 &position,D3DXVECTOR3 &poi, D3DXVECTOR3 &up)
{
	this->position = position;
	D3DXMatrixLookAtLH(&view, &position, &poi, &up);
	D3DXMatrixPerspectiveFovLH(&projection, 30.0f, 1.7777f, 0.1f, 1000.0f);
}

Camera::~Camera(void)
{
}
