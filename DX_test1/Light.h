#pragma once
#include "D3D.h"

class Light
{
public:
	Light(void);
	Light(D3DXVECTOR3 &position, D3DXCOLOR &diffuseColor, D3DXCOLOR &ambientColor, float diffuseIntensity, float ambientIntensity);
	~Light(void);

	D3DXVECTOR3 position;
	D3DXCOLOR diffuseColor;
	D3DXCOLOR ambientColor;
	float diffuseIntensity;
	D3DXVECTOR3 ambientIntensity;

};
