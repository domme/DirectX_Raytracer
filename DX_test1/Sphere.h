#pragma once
#include "mesh.h"
#include "IntersectionInfo.h"
#include "Ray.h"
#include "D3D.h"

class Sphere :
	public Mesh
{
public:
	Sphere(void);
	Sphere(Material* material, D3DXVECTOR3 &position, float radius);
	virtual ~Sphere(void);
	
	float radius;
	IntersectionInfo testIntersection(Ray* ray);
	D3DXCOLOR shade(vector<Light*>* lightList, vector<Mesh*>* objectList, Camera* cam);
	
};
