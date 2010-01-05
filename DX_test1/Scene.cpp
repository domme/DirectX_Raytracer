#include "StdAfx.h"
#include "Scene.h"


Scene::Scene(void)
{
}

Scene::Scene(std::vector<Mesh*> &objectList,std::vector<Light*> &lightList, Camera &camera)
{
	this->objectList = objectList;
	this->lightList = lightList;
	this->camera = camera;
}

D3DXCOLOR Scene::trace(Ray &ray)
{
	objectInstersectionList.clear();

	for(int i = 0; i < objectList.size(); i++)
		if(objectList[i]->testIntersection(ray).hasIntersected)
			objectInstersectionList.push_back(objectList[i]);

	//was any object hit?
	if(objectInstersectionList.size() > 0)
	{
		float minZ = objectInstersectionList[0]->position.z;

		for(int i = 0; i < objectInstersectionList.size(); i++)
			if(objectInstersectionList[i]->position.z < minZ)
				minZ = objectInstersectionList[i]->position.z;

		Mesh* hitMesh;

		for(int i = 0; i < objectInstersectionList.size(); i++)
			if(objectInstersectionList[i]->position.z == minZ)
				hitMesh = objectInstersectionList[i];
	}


	return D3DXCOLOR();
}



Scene::~Scene(void)
{
}
