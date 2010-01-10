#pragma once
#include "D3D.h"
#include "Material.h"

class LambertMaterial : public Material
{
public:
	LambertMaterial(void);
	LambertMaterial(D3DXCOLOR &color);
	~LambertMaterial(void);

	
	D3DXCOLOR shade(vector<Light*>* lightList, vector<Mesh*>* objectList, Mesh* object, Camera* cam);

};
