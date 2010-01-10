#pragma once
#include "D3D.h"

class IntersectionInfo
{
public:
	IntersectionInfo(void);
	~IntersectionInfo(void);

	bool hasIntersected;
	float intersectionParameter;
	D3DXVECTOR3 intersectionPoint;
	D3DXVECTOR3 intersectionNormal;
	D3DXVECTOR3 intersectionNormalLong;

};
