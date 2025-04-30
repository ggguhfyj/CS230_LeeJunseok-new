/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Texture.h
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 8, 2023
Updated:    March 23, 2023
*/

#pragma once
#include "Vec2.h"
#include <filesystem>
#include <raylib.h>
#include "matrix.h"
namespace CS230 {
    class Texture {
    public:
        Texture();
        Texture(const std::filesystem::path& file_name);
        ~Texture();

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;
        Texture(Texture&& temporary) noexcept;
        Texture& operator=(Texture&& temporary) noexcept;


        void Load(const std::filesystem::path& file_name);
        void Draw(Math::vec2 location);
        void Draw(Math::TransformationMatrix display_matrix);
        Math::ivec2 GetSize() const;

    private:
        Texture2D texture;
    };
}
