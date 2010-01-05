#pragma once
#include "Material.h"
#include "D3D.h"
#include "Ray.h"
#include "IntersectionInfo.h"

class Mesh
{
public:
	Mesh(void);
	Mesh(Material &material, D3DXVECTOR3 &position);
	~Mesh(void);

	Material material;
	D3DXVECTOR3 position;

	virtual IntersectionInfo testIntersection(Ray &ray) = 0;
	
	
};
