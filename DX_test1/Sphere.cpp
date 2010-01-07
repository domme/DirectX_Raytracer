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
	returnInfo.hasIntersected = false;

	float B, C, t0, t1;
	B = 2 * (ray->direction.x * (ray->startPosition.x - position.x) + ray->direction.y * (ray->startPosition.y - position.y) + ray->direction.z * (ray->startPosition.z - position.z));
	C = pow((ray->startPosition.x - position.x), 2) + pow((ray->startPosition.y - position.y), 2) + pow((ray->startPosition.z - position.z), 2) - radius * radius;

	float determina = B * B - 4 * C;

	if(determina < 0)
		return returnInfo; //no hit

	t0 = (-B + sqrtf(determina))/2.0f;
	t1 = (-B - sqrtf(determina))/2.0f;

	if(t0 < t1)
	{
		returnInfo.hasIntersected = true;
		returnInfo.intersectionParameter = t0;
		return returnInfo;
	}

	if(t1 < t0)
	{
		returnInfo.hasIntersected = true;
		returnInfo.intersectionParameter = t1;
		return returnInfo;
	}

	return returnInfo;
}

D3DXCOLOR Sphere::shade(Ray* ray, vector<Light*>* lightList, vector<Mesh*>* objectList)
{
	return this->material.color;
}

Sphere::~Sphere(void)
{
}
