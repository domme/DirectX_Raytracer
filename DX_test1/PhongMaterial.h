#pragma once
#include "material.h"
#include "D3D.h"

class PhongMaterial :
	public Material
{
public:
	PhongMaterial(void);
	PhongMaterial(D3DXCOLOR &color);
	PhongMaterial(D3DXCOLOR &color, float ks, float kse);
	~PhongMaterial(void);


	float ks;
	float kse;
	D3DXCOLOR shade(vector<Light*>* lightList, vector<Mesh*>* objectList, Mesh* object, Camera* cam);

};
