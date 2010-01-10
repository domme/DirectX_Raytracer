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
	this->kd = 1.0f;
	this->ks = ks;
	this->kse = kse;
}

D3DXCOLOR PhongMaterial::shade(vector<Light*>* lightList, vector<Mesh*>* objectList, Mesh* object, Camera* cam)
{
	float Idiff, Ispec;
	Idiff = 0.0f;
	Ispec = 0.0f;
	D3DXCOLOR returnColor = color;
	D3DXCOLOR specularColor = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
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
			
			Ispec += ks * pow(sDot, kse);

			if(Ispec > 1.0f)
				Ispec = 1.0f;
			if(Ispec < 0.0f)
				Ispec = 0.0f;
		
			Idiff += kd * dDot;
			//I +=  ks * pow(sDot, kse);
		}
	}
	
	if(inShadow)
		Idiff = lights[0]->ambientIntensity.x;

	else
		Idiff += lights[0]->ambientIntensity.x;

	returnColor *= Idiff;
	specularColor *= Ispec;

	D3DXCOLOR addedColor;
	D3DXColorAdd(&addedColor, &returnColor, &specularColor);

	if(addedColor.r > 255.0f)
		addedColor.r = 255.0f;
	if(addedColor.g > 255.0f)
		addedColor.g = 255.0f;
	if(addedColor.b > 255.0f)
		addedColor.b = 255.0f;

	return addedColor;
}

PhongMaterial::~PhongMaterial(void)
{
}
