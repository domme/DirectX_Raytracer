#include "StdAfx.h"
#include "IntersectionInfo.h"


IntersectionInfo::IntersectionInfo(void)
{
	hasIntersected = false;
	intersectionParameter = 0.0f;
	intersectionNormal = *new D3DXVECTOR3();
	intersectionNormalLong = *new D3DXVECTOR3();
	intersectionPoint = *new D3DXVECTOR3();
}

IntersectionInfo::~IntersectionInfo(void)
{
}
