#include "StdAfx.h"
#include "Sphere.h"

Sphere::Sphere(void) 
{
	radius = 1.0f;
}

Sphere::Sphere(Material &material, D3DXVECTOR3 &position, float radius) : Mesh(Material &material, D3DXVECTOR3 &position)
{
	this->radius = radius;
}

IntersectionInfo Sphere::testIntersection(Ray &ray)
{
	
}

Sphere::~Sphere(void)
{
}
