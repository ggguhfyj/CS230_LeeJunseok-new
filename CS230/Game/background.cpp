/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Background.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes,Junseok Lee
Created:    April 2025
*/
#include "background.h"
#include "../Engine/Engine.h"


void Background::Add(const std::filesystem::path& texture_path, double speed) {
    auto texture = Engine::GetTextureManager().Load(texture_path);
	backgrounds.push_back(ParallaxLayer{ texture, speed });
}

void Background::Unload()
{
	backgrounds.clear(); //clear all elements withing vector
}

void Background::Draw(const CS230::Camera& camera) {

    for (auto& a : backgrounds) {
        Math::vec2 cposition = Math::vec2{ 0 - camera.GetPosition().x * a.speed, 0 - camera.GetPosition().y * a.speed };
        Math::TranslationMatrix matrix(cposition);
        a.texture->Draw(matrix);
    }

}

Math::ivec2 Background::GetSize() {
    return backgrounds[backgrounds.size() - 1].texture->GetSize();
}