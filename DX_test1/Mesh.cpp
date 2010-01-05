#include "StdAfx.h"
#include "Mesh.h"

Mesh::Mesh(void)
{
	material = Material();

}

Mesh::Mesh(Material &material, D3DXVECTOR3 &position)
{
	this->material = material;
	this->position = position;
	this-> radius = radius;
}



Mesh::~Mesh(void)
{
}
