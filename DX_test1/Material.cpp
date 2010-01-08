#include "StdAfx.h"
#include "Material.h"

Material::Material(void)
{
	this->color = D3DXCOLOR(255.0f, 0.0f, 0.0f, 255.0f);
	kd = 1.0f;
}

Material::Material(D3DXCOLOR &color)
{
	this->color = color;
	kd = 1.0f;
}

Material::~Material(void)
{
}
