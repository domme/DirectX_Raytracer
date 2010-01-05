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

IntersectionInfo Sphere::testIntersection(Ray &ray)
{
	return IntersectionInfo();
}

D3DXCOLOR Sphere::shade(Ray &ray, vector<Light*> &lightList, vector<Mesh*> &objectList)
{
	return this->material.color;
}

Sphere::~Sphere(void)
{
}
