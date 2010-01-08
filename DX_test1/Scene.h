#pragma once
#include <iostream>
#include "stdafx.h"
#include "Mesh.h"
#include "Ray.h"
#include "Camera.h"
#include <vector>
#include "Light.h"

using namespace std;

class Scene
{
public:
	Scene(void);
	Scene(vector<Mesh*> &objectList,vector<Light*> &lightList, Camera &camera);
	~Scene(void);

	Camera camera;
	vector<Mesh*>objectList;
	vector<Light*>lightList;
	D3DXCOLOR trace(Ray* ray);

private:
	vector<Mesh*> objectInstersectionList;
	bool checkObjectList();

	

	
};
