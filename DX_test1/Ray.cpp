#include "StdAfx.h"
#include "Ray.h"

Ray::Ray(void)
{
	this->direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	this->startPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->intersectionParameter = 1.0f;
}

Ray::Ray(D3DXVECTOR3 &startPosition, D3DXVECTOR3 &direction)
{
	this->direction = direction;
	this->startPosition = startPosition;
	this->intersectionParameter = 1.0f;
}


D3DXVECTOR3 Ray::calculateIntersectionPoint()
{
	return (this->startPosition + intersectionParameter * this->direction);
}

Ray::~Ray(void)
{
}
