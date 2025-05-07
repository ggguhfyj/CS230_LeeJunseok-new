#include "GameObjectManager.h"

void CS230::GameObjectManager::Add(GameObject* object)
{
	objects.push_back(object);
}

void CS230::GameObjectManager::Unload()
{
	for (GameObject* doodoo : objects)
	{
		delete(doodoo);
	}
	objects.clear();
}

void CS230::GameObjectManager::UpdateAll(double dt)
{
	for (GameObject* doodoo : objects)
	{
		doodoo->Update(dt);
	}
}

void CS230::GameObjectManager::DrawAll(Math::TransformationMatrix camera_matrix)
{
	for (GameObject* doodoo : objects)
	{
		doodoo->Draw(camera_matrix);
	}
}
