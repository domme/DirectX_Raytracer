#pragma once
#include <iostream>
#include "stdafx.h"
#include "Mesh.h"
#include "Ray.h"
#include <vector>

using namespace std;

class Scene
{
public:
	Scene(void);
	Scene(vector<Mesh> &objectList);
	~Scene(void);


	vector<Mesh>objectList;
	D3DXCOLOR trace(Ray &ray);

private:
	vector<Mesh> objectInstersectionList;

	
};
