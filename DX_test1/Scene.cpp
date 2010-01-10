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
	bool sorted = false;

	/*while(!sorted)
	{
		for(int i = 0; i < objectList.size(); i++)
		{
			if(i < objectList.size() - 1)
			{
				if(D3DXVec3Length(&(objectList[i + 1]->position - camera.position)) < D3DXVec3Length(&(objectList[i]->position - camera.position)))
				{
					Mesh** smaller;
					Mesh** bigger;
					smaller = &objectList[i + 1];
					bigger = &objectList[i];

					objectList[i] = *smaller;
					objectList[i+1] = *bigger;
				}
			}
		}
		sorted = checkObjectList();*/
		
//}
	
	
}

bool Scene::checkObjectList()
{
	for(int i = 0; i < objectList.size(); i++)
	{
		if( i < objectList.size() -1)
		{
			if(!(D3DXVec3Length(&(objectList[i]->position - camera.position)) < D3DXVec3Length(&(objectList[i + 1]->position - camera.position))))
			{
				return false;
			}
		}
	}

	return true;
}

D3DXCOLOR Scene::trace(Ray* ray)
{
	objectInstersectionList.clear();
	IntersectionInfo* info = new IntersectionInfo();

	for(int i = 0; i < objectList.size(); i++)
	{
		info = &objectList[i]->testIntersection(ray);
		if(info->hasIntersected == true)
		{
			//return objectList[i]->shade(ray, &lightList, &objectList, info);
			objectList[i]->info = *info;
			objectInstersectionList.push_back(objectList[i]);
		}
	}

	if(objectInstersectionList.size() > 0)
	{
		Mesh* hitMesh;
		float minDistance = D3DXVec3Length(&(objectInstersectionList[0]->position - camera.position));

		for(int i = 0; i < objectInstersectionList.size(); i++)
		{
			float currDistance =  D3DXVec3Length(&(objectInstersectionList[i]->position - camera.position));
			if(currDistance < minDistance)
			{
				minDistance = currDistance;
			}
		}

		for(int i = 0; i < objectInstersectionList.size(); i++)
		{
			if(abs(D3DXVec3Length(&(objectInstersectionList[i]->position - camera.position)) - minDistance) < 0.1f)
				hitMesh = objectInstersectionList[i];
		}

		return hitMesh->shade(&lightList, &objectList, &camera);
	}



	return D3DXCOLOR(128.0f, 128.0f, 128.0f, 255.0f);
}



Scene::~Scene(void)
{
}
