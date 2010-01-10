#pragma once
#include "D3D.h"
#include "Ray.h"
#include "IntersectionInfo.h"
#include <vector>
#include "Light.h"
#include "Material.h"
#include "Camera.h"

using namespace std;

class Mesh
{
public:
	Mesh(void);
	Mesh(Material* material, D3DXVECTOR3 &position);
	virtual ~Mesh(void);
	
	
	Material* material;
	D3DXVECTOR3 position;
	IntersectionInfo info;

	virtual IntersectionInfo testIntersection(Ray* ray) = 0;
	

	virtual D3DXCOLOR shade(vector<Light*>* lightList, vector<Mesh*>* objectList, Camera* cam)  = 0;
};
