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
#include "Engine.h"
#include "Sprite.h"

namespace CS230 {

    Sprite::Sprite():current_frame(0) {
    }
   
    void CS230::Sprite::Load(const std::filesystem::path& sprite_file) {
        if (sprite_file.extension() != ".spt") {
            throw std::runtime_error(sprite_file.generic_string() + " is not a .spt file");
        }
        std::ifstream in_file(sprite_file);

        if (in_file.is_open() == false) {
            throw std::runtime_error("Failed to load " + sprite_file.generic_string());
        }

        hotspots.clear();
        frame_texels.clear();

        std::string text;
        in_file >> text;
        texture.Load(text);
        frame_size = texture.GetSize();

        in_file >> text;
        while (in_file.eof() == false) {
            if (text == "FrameSize") {
                in_file >> frame_size.x;
                in_file >> frame_size.y;
            }
            else if (text == "NumFrames") {
                int frame_count;
                in_file >> frame_count;
                for (int i = 0; i < frame_count; i++) {
                    frame_texels.push_back({ frame_size.x * i, 0 });
                }
            }
            else if (text == "Frame") {
                int frame_location_x, frame_location_y;
                in_file >> frame_location_x;
                in_file >> frame_location_y;
                frame_texels.push_back({ frame_location_x, frame_location_y });
            }
            else if (text == "HotSpot") {
                int hotspot_x, hotspot_y;
                in_file >> hotspot_x;
                in_file >> hotspot_y;
                hotspots.push_back({ hotspot_x, hotspot_y });
            }
            else {
                Engine::GetLogger().LogError("Unknown command: " + text);
            }
            in_file >> text;
        }
        if (frame_texels.empty() == true) {
            frame_texels.push_back({ 0,0 });
        }
    }


    Math::ivec2 Sprite::GetHotSpot(int index) {
        return hotspots[index];
    }
    Math::ivec2 Sprite::GetFrameTexel(int index) const
    {
        if ((index >= 0) && (index < frame_texels.size()))
        {
            return frame_texels.at(index);
        }
        else
        {
            Engine::GetLogger().LogError("index error at Sprite.cpp GetFrameTexel");
            return { 0,0 };
        }
    }
    Math::ivec2 Sprite::GetFrameSize()
    {

        return frame_size;
    }
    void Sprite::ShowFrame(int index)
    {
        if ((index >= 0) && (index < frame_texels.size()))
        {
            current_frame = index;
        }
        else
        {
            Engine::GetLogger().LogError("index error at Sprite.cpp ShowFrame");
            current_frame = 0;
        }
    }
    void CS230::Sprite::Draw(Math::TransformationMatrix display_matrix) {
        texture.Draw(display_matrix * Math::TranslationMatrix(-GetHotSpot(0)), GetFrameTexel(current_frame), GetFrameSize());
    }

}