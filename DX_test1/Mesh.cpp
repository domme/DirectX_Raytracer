#include "StdAfx.h"
#include "Mesh.h"
#include "LambertMaterial.h"


Mesh::Mesh(void)
{
	material = new LambertMaterial();

}

Mesh::Mesh(Material* material, D3DXVECTOR3 &position)
{
	this->material = material;
	this->position = position;
}




Mesh::~Mesh(void)
{
}
 
