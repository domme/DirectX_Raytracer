#include "StdAfx.h"
#include "Sphere.h"
#include "Material.h"
#include <math.h>

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

	if(t0 < t1 && t0 > 0.1f)
	{
		returnInfo.hasIntersected = true;
		returnInfo.intersectionParameter = t0;
		ray->intersectionParameter = t0;
		returnInfo.intersectionPoint = ray->calculateIntersectionPoint();
		D3DXVECTOR3 intersectionNormal = returnInfo.intersectionPoint - position;
		D3DXVec3Normalize(&returnInfo.intersectionNormal, &intersectionNormal);
		return returnInfo;
	}

	if(t1 <= t0 && t1 > 0.1f)
	{
		returnInfo.hasIntersected = true;
		returnInfo.intersectionParameter = t1;
		ray->intersectionParameter = t1;
		returnInfo.intersectionPoint = ray->calculateIntersectionPoint();
		D3DXVECTOR3 intersectionNormal = returnInfo.intersectionPoint - position;
		D3DXVec3Normalize(&returnInfo.intersectionNormal, &intersectionNormal);
		return returnInfo;
	}

	return returnInfo;
}

D3DXCOLOR Sphere::shade(vector<Light*>* lightList, vector<Mesh*>* objectList)
{
	

	D3DXCOLOR returnColor(0.0f, 0.0f, 0.0f, 0.0f); //start with black
	vector<Light*> lights = *lightList;
	D3DXVECTOR3 L, Lnorm;
	D3DXVECTOR3 N = info.intersectionNormal;
	D3DXCOLOR Ca;
	float	  Ia;
	float	  kd = material.kd;
	D3DXCOLOR Da;
	float	  Id;
	float I = 0;

	
	for( int i = 0; i < lights.size(); i++)
	{
		Ca = lights[i]->ambientColor;
		Ia = lights[i]->ambientIntensity;
		Da = lights[i]->diffuseColor;
		
		L = lights[i]->position - info.intersectionPoint;
		D3DXVec3Normalize(&Lnorm, &L);
		float dot = D3DXVec3Dot(&N, &Lnorm);
		if(dot < 0.0f)
			dot = 0.0f;
		if(dot > 1.0f)
			dot = 1.0f;
		I +=  kd * dot;
	}
	
	I +=  Ia;
	if(I > 1.0f)
		I = 1.0f;
	return material.color * I;

//	return material.color;
}

Sphere::~Sphere(void)
{
}
