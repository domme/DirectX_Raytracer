#include "StdAfx.h"
#include "Sphere.h"
#include "Material.h"
#include <math.h>

Sphere::Sphere(void) 
{
	radius = 1.0f;
}

Sphere::Sphere(Material* material, D3DXVECTOR3 &position, float radius) : Mesh(material, position)
{
	this->radius = radius;
}

IntersectionInfo Sphere::testIntersection(Ray* ray)
{
	IntersectionInfo returnInfo = *new IntersectionInfo();
	returnInfo.hasIntersected = false;

	float B, C, t0, t1;
	B = 2 * (ray->direction.x * (ray->startPosition.x - position.x) + ray->direction.y * (ray->startPosition.y - position.y) + ray->direction.z * (ray->startPosition.z - position.z));
	C = pow((ray->startPosition.x - position.x), 2) + pow((ray->startPosition.y - position.y), 2) + pow((ray->startPosition.z - position.z), 2) - radius * radius;

	float determina = B * B - 4 * C;

	if(determina < 0)
		return returnInfo; //no hit

	t0 = (-B + sqrtf(determina))/2.0f;
	t1 = (-B - sqrtf(determina))/2.0f;

	if(t0 < t1 && t0 > 0.0f)
	{
		returnInfo.hasIntersected = true;
		returnInfo.intersectionParameter = t0;
		ray->intersectionParameter = t0;
		returnInfo.intersectionPoint = ray->calculateIntersectionPoint();
		D3DXVECTOR3 intersectionNormal = returnInfo.intersectionPoint - position;
		returnInfo.intersectionNormalLong = intersectionNormal;
		D3DXVec3Normalize(&returnInfo.intersectionNormal, &intersectionNormal);
		return returnInfo;
	}

	if(t1 <= t0 && t1 > 0.0f)
	{
		returnInfo.hasIntersected = true;
		returnInfo.intersectionParameter = t1;
		ray->intersectionParameter = t1;
		returnInfo.intersectionPoint = ray->calculateIntersectionPoint();
		D3DXVECTOR3 intersectionNormal = returnInfo.intersectionPoint - position;
		returnInfo.intersectionNormalLong = intersectionNormal;
		D3DXVec3Normalize(&returnInfo.intersectionNormal, &intersectionNormal);
		return returnInfo;
	}

	return returnInfo;
}

D3DXCOLOR Sphere::shade(vector<Light*>* lightList, vector<Mesh*>* objectList, Camera* cam)
{
	return material->shade(lightList, objectList, this, cam);
}

Sphere::~Sphere(void)
{
}
