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
	float bias = 0.01f;
	IntersectionInfo returnInfo;
	float k;
	
	//calculate intersection coefficient ray<->sphere
	k = (pow(radius, 2) - pow((ray->startPosition.x - position.x), 2) - pow((ray->startPosition.y - position.y), 2) - pow((ray->startPosition.z - position.z), 2)) 
		/ (pow(ray->direction.x, 2) + pow(ray->direction.y, 2) + pow(ray->direction.z, 2));

	if((ray->startPosition + k*ray->direction) < D3DXVECTOR3(bias, bias, bias))
	{
		returnInfo.hasIntersected = true;
		returnInfo.intersectionParameter = k;
	}
	
	else
		returnInfo.hasIntersected = false;
	
	return returnInfo;
}

D3DXCOLOR Sphere::shade(Ray &ray, vector<Light*> &lightList, vector<Mesh*> &objectList)
{
	return this->material.color;
}

Sphere::~Sphere(void)
{
}
