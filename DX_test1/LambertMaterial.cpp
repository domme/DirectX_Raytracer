#include "StdAfx.h"
#include "LambertMaterial.h"
#include "Mesh.h"
#include "Ray.h"

LambertMaterial::LambertMaterial(void)
{
	this->color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	kd = 1.0f;
}

LambertMaterial::LambertMaterial(D3DXCOLOR &color)
{
	this->color = color;
	kd = 1.0f;
}

D3DXCOLOR LambertMaterial::shade(vector<Light *> *lightList, vector<Mesh *> *objectList, Mesh *object, Camera* cam)
{
	float Idiff;
	Idiff = 0.0f;
	D3DXCOLOR returnColor = color;
	D3DXVECTOR3 L, Lnorm;
	bool inShadow = false;
	vector<Mesh*> objs = *objectList;
	vector<Light*> lights = *lightList;

	for(int l = 0; l < lights.size(); l++)
	{
		L = lights[l]->position - object->info.intersectionPoint;
		D3DXVec3Normalize(&Lnorm, &L);

		Ray lightRay(object->info.intersectionPoint, Lnorm);

		for(int i = 0; i < objs.size(); i++)
			if(objs[i]->testIntersection(&lightRay).hasIntersected)
				inShadow = true;

		if(!inShadow)
		{
			float dDot = D3DXVec3Dot(&object->info.intersectionNormal, &Lnorm);
			if(dDot < 0.0f)
				dDot = 0.0f;
			if(dDot > 1.0f)
				dDot = 1.0f;
		
			Idiff += kd * dDot;
		}
	}
	
	if(inShadow)
		Idiff = lights[0]->ambientIntensity.x;

	else
		Idiff += lights[0]->ambientIntensity.x;

	returnColor *= Idiff;
	if(returnColor.r > 255.0f)
		returnColor.r = 255.0f;
	if(returnColor.g > 255.0f)
		returnColor.g = 255.0f;
	if(returnColor.b > 255.0f)
		returnColor.b = 255.0f;

	return returnColor;

}
