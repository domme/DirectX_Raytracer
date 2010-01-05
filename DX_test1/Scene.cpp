#include "StdAfx.h"
#include "Scene.h"

Scene::Scene(void)
{
}

Scene::Scene(std::vector<Mesh> &objectList)
{
	this->objectList = objectList;
}

D3DXCOLOR Scene::trace(Ray &ray)
{
	objectInstersectionList.clear();

	for(int i = 0; i < objectList.size; i++)
		if(objectList[i].testIntersection(ray).hasIntersected)
			objectInstersectionList.push_back(objectList[i]);

	if(objectInstersectionList.size > 0)
		float minDistance = objectInstersectionList[0].t;

	for(int i = 0; i < objectInstersectionList.size; i++)

		
}

Scene::~Scene(void)
{
}
