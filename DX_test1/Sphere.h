#pragma once
#include "mesh.h"

class Sphere :
	public Mesh
{
public:
	Sphere(void);
	Sphere(Material &material, D3DXVECTOR3 &position, float radius);
	~Sphere(void);
	
	float radius;
	
};
