#include "StdAfx.h"
#include "PhongMaterial.h"
#include "Mesh.h"

PhongMaterial::PhongMaterial(void)
{
	this->color = D3DXCOLOR(255.0f, 0.0f, 0.0f, 255.0f);
	this->kd = 1.0f;
	this->ks = 3.0f;
	this->kse = 2.0f;
}


PhongMaterial::PhongMaterial(D3DXCOLOR &color)
{
	this->color = color;
	this->kd = 1.0f;
	this->ks = 3.0f;
	this->kse = 2.0f;
}

PhongMaterial::PhongMaterial(D3DXCOLOR &color, float ks, float kse)
{
	this->color = color;
	this->kd = .5f;
	this->ks = ks;
	this->kse = kse;
}

D3DXCOLOR PhongMaterial::shade(vector<Light*>* lightList, vector<Mesh*>* objectList, Mesh* object, Camera* cam)
{
	float I = 0;
	D3DXCOLOR returnColor = color;
	D3DXVECTOR3 L, Lnorm, R, Rnorm, V, Vnorm;
	V = cam->position - object->info.intersectionPoint;
	D3DXVec3Normalize(&Vnorm, &V);
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
			R = 2 * D3DXVec3Dot(&object->info.intersectionNormal, &Lnorm) * object->info.intersectionNormal- Lnorm;
			D3DXVec3Normalize(&Rnorm, &R);
			
			float dDot = D3DXVec3Dot(&object->info.intersectionNormal, &Lnorm);
			if(dDot < 0.0f)
				dDot = 0.0f;
			if(dDot > 1.0f)
				dDot = 1.0f;

			float sDot = D3DXVec3Dot(&Vnorm, &Rnorm);
			if(sDot < 0.0f)
				sDot = 0.0f;
			if(sDot > 1.0f)
				sDot = 1.0f;

		
			I += kd * dDot + ks * pow(sDot, kse);
			//I +=  ks * pow(sDot, kse);
		}
	}
	
	if(inShadow)
		I = lights[0]->ambientIntensity.x;

	else
		I += lights[0]->ambientIntensity.x;

	return returnColor * I;
}

PhongMaterial::~PhongMaterial(void)
{
}
