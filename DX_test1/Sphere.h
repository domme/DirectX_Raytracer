#pragma once
#include "mesh.h"

class Sphere :
	public Mesh
{
public:
	Sphere(void);
	Sphere(Material &material, D3DXVECTOR3 &position, float radius) : Mesh(Material &material, D3DXVECTOR3 &position);
	~Sphere(void);
	
	float radius;
	
};
