/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  TextureManager.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes junseok lee
Created:    March 8, 2023
*/

#include "TextureManager.h"
#include "Texture.h"
#include "Engine.h"

CS230::Texture * CS230::TextureManager::Load(const std::filesystem::path & file_name) //pass by value?
{
	for (auto a : textures)
	{
		if (file_name == a.first)
		{
			return a.second;
		}
	}
	Engine::GetLogger().LogEvent("Currently loading texture: " + file_name.string());

	CS230::Texture* Ntexture = new CS230::Texture(file_name); //kinda like a wrapper function for the raylib version.
	textures[file_name] = Ntexture;
	return Ntexture;
}

void CS230::TextureManager::Unload()
{
	Engine::GetLogger().LogEvent("unloading textures");
	for (auto& a : textures)
	{
		delete a.second;
	}
	textures.clear();
}
