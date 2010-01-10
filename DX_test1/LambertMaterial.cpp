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
	D3DXCOLOR returnColor(0.0f, 0.0f, 0.0f, 0.0f); //start with black
	vector<Light*> lights = *lightList;
	D3DXVECTOR3 L, Lnorm;
	D3DXVECTOR3 N = object->info.intersectionNormal;
	D3DXCOLOR Ca;
	D3DXVECTOR3 Ia;
	D3DXCOLOR Da;
	float	  Id;
	D3DXVECTOR3 I(0.0f, 0.0f, 0.0f);
	bool inShadow = false;

	
	for( int i = 0; i < lights.size(); i++)
	{
		inShadow = false;
		Ca = lights[i]->ambientColor;
		Ia = lights[i]->ambientIntensity;
		Da = lights[i]->diffuseColor;
		
		L = lights[i]->position - object->info.intersectionPoint;
		D3DXVec3Normalize(&Lnorm, &L);

		Ray lightRay(object->info.intersectionPoint, Lnorm);
		vector<Mesh*> objList = *objectList;

		for(int j = 0; j < objList.size(); j++)
			if(objList[j]->testIntersection(&lightRay).hasIntersected)
				inShadow = true;

		if(!inShadow)
		{
			float dot = D3DXVec3Dot(&N, &Lnorm);
			if(dot < 0.0f)
				dot = 0.0f;
			if(dot > 1.0f)
				dot = 1.0f;
		
		
			float addI = kd * dot;

			I.x +=   addI;
			I.y +=   addI;
			I.z +=   addI;
		
		}
	}
	
	if(inShadow)
		I = Ia; //set intensity to ambient part

	else
		I +=  Ia; //add ambient part to calculated intensity

	if(I.x > 1.0f)
		I.x = 1.0f;
	
	if(I.y > 1.0f)
		I.y = 1.0f;

	if(I.z > 1.0f)
		I.z = 1.0f;


	returnColor.r =   color * I.x;
	returnColor.g =   color * I.y;
	returnColor.b =   color * I.z;

	return  returnColor;

}
