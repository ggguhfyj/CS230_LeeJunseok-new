/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Sprite.cpp
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 8, 2023
Updated:    March 23, 2023
*/

#include "Sprite.h"

namespace CS230 {

    Sprite::Sprite() {
    }
    void Sprite::Load(const std::filesystem::path& texture_path) {
        texture.Load(texture_path);
        Math::ivec2 texSize = GetTextureSize();
        hotspots.clear();
        hotspots.push_back({ texSize.x / 2, texSize.y / 2 });
    }
    void Sprite::Load(const std::filesystem::path& texture_path, Math::ivec2 hotspot_position) {
        texture.Load(texture_path);
        hotspots.clear();
        hotspots.push_back(hotspot_position);
    }
    void Sprite::Load(const std::filesystem::path& texture_path, std::initializer_list<Math::ivec2> spots) {
        texture.Load(texture_path);
        for (Math::ivec2 spot : spots) {
            hotspots.push_back(spot);
        }
    }

    Math::ivec2 Sprite::GetTextureSize() {
        return texture.GetSize();
    }

    Math::ivec2 Sprite::GetHotSpot(int index) {
        return hotspots[index];
    }

    void Sprite::Draw(Math::TransformationMatrix display_matrix) {
        Math::ivec2 hotspot = GetHotSpot(0);
        texture.Draw(display_matrix * Math::TranslationMatrix(-hotspot));
    }

}