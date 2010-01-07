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

D3DXCOLOR Scene::trace(Ray* ray)
{
	for(int i = 0; i < objectList.size(); i++)
	{
		if(objectList[i]->testIntersection(ray).hasIntersected == true)
			return objectList[i]->shade(ray, &lightList, &objectList);
	}

	
	////was any object hit?
	//if(objectInstersectionList.size() > 0)
	//{
	//	float minZ = objectInstersectionList[0]->position.z;

	//	for(int i = 0; i < objectInstersectionList.size(); i++)
	//		if(objectInstersectionList[i]->position.z < minZ)
	//			minZ = objectInstersectionList[i]->position.z;

	//	Mesh* hitMesh;

	//	for(int i = 0; i < objectInstersectionList.size(); i++)
	//		if(objectInstersectionList[i]->position.z == minZ)
	//			hitMesh = objectInstersectionList[i];

	//	return hitMesh->shade(ray, lightList, objectList);
	//}


	return D3DXCOLOR(128.0f, 128.0f, 128.0f, 255.0f);
}



Scene::~Scene(void)
{
}
