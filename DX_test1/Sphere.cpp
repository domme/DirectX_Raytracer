#include "StdAfx.h"
#include "Sphere.h"
#include "Material.h"

Sphere::Sphere(void) 
{
	radius = 1.0f;
}

Sphere::Sphere(Material &material, D3DXVECTOR3 &position, float radius) : Mesh(material, position)
{
	this->radius = radius;
}

IntersectionInfo Sphere::testIntersection(Ray* ray)
{
	IntersectionInfo returnInfo;
	float k, k1, k2;
	float A, B, C;
	
	A = D3DXVec3Dot(&ray->direction, &ray->direction); 
	B = 2 * D3DXVec3Dot(&ray->direction, &ray->startPosition);
	C = D3DXVec3Dot( &ray->startPosition, &ray->startPosition) - radius * radius;

	float disc = B * B - 4 * A * C;

	if (disc < 0)
		return returnInfo;

	float discSqrt = sqrtf(disc);
	float q;

	if(B < 0)
		q = (-B - discSqrt) / 2.0f;
	else
		q = (-B + discSqrt) / 2.0f;

	float t0 = q/ A;
	float t1 = C/ q;

	if( t0 > t1)
	{
		float temp = t0;
		t0 = t1;
		t1 = temp;
	}

	if (t1 < 0)
		return returnInfo;

	if( t0 < 0)
	{
		returnInfo.intersectionParameter = t1;
		returnInfo.hasIntersected = true;
		return returnInfo;
	}

	else
	{
		returnInfo.intersectionParameter = t0;
		returnInfo.hasIntersected = true;
		return returnInfo;
	}
	
	
	return returnInfo;
}

D3DXCOLOR Sphere::shade(Ray &ray, vector<Light*> &lightList, vector<Mesh*> &objectList)
{
	return this->material.color;
}

Sphere::~Sphere(void)
{
}
