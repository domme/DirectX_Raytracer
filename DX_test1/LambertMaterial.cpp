#include "StdAfx.h"
#include "LambertMaterial.h"
#include "Mesh.h"

LambertMaterial::LambertMaterial(void)
{
	this->color = D3DXCOLOR(255.0f, 0.0f, 0.0f, 255.0f);
	kd = 1.0f;
}

LambertMaterial::LambertMaterial(D3DXCOLOR &color)
{
	this->color = color;
	kd = 1.0f;
}

D3DXCOLOR LambertMaterial::shade(vector<Light *> *lightList, vector<Mesh *> *objectList, Mesh *object)
{
	D3DXCOLOR returnColor(0.0f, 0.0f, 0.0f, 0.0f); //start with black
	vector<Light*> lights = *lightList;
	D3DXVECTOR3 L, Lnorm;
	D3DXVECTOR3 N = object->info.intersectionNormal;
	D3DXCOLOR Ca;
	float	  Ia;
	D3DXCOLOR Da;
	float	  Id;
	float I = 0;

	
	for( int i = 0; i < lights.size(); i++)
	{
		Ca = lights[i]->ambientColor;
		Ia = lights[i]->ambientIntensity;
		Da = lights[i]->diffuseColor;
		
		L = lights[i]->position - object->info.intersectionPoint;
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
	return color * I;

}
