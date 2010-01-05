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

IntersectionInfo Mesh::testIntersection(Ray &ray)
{
	return IntersectionInfo();
}

Sphere::~Sphere(void)
{
}
