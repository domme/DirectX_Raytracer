#pragma once
#include "D3D.h"

class Camera
{
public:
	Camera(void);
	Camera(D3DXVECTOR3* position,D3DXVECTOR3* poi, D3DXVECTOR3* up);
	~Camera(void);

	D3DXVECTOR3 position;
	D3DXMATRIX view;
	D3DXMATRIX projection;
};
