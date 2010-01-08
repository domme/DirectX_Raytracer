#pragma once
#include "D3D.h"

class Ray
{
public:
	Ray(void);
	Ray(D3DXVECTOR3 &startPosition, D3DXVECTOR3 &direction);
	~Ray(void);

	D3DXVECTOR3 direction;
	D3DXVECTOR3 startPosition;
	float intersectionParameter; 

	D3DXVECTOR3 calculateIntersectionPoint();
	
};
