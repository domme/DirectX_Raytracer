#pragma once
#include "D3D.h"

class Material
{
public:
	Material(void);
	Material(D3DXCOLOR &color);
	~Material(void);

	D3DXCOLOR color;
	float kd;


};
