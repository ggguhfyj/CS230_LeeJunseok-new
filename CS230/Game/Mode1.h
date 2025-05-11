/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.h
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 11, 2025
Updated:    March 23, 2025
*/

#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "../Engine/Sprite.h"
#include "../Engine/Vec2.h"
#include <vector>
#include "background.h"
#include "..\Engine\GameObjectManager.h"
#include "Crates.h"
#include "Robot.h"
class Cat;
class Asteroid;


class Mode1 : public CS230::GameState {
public:
    Mode1();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    //void Clear();
    void Draw() override;
    std::string GetName() override {
        return "Mode1";
    }
    static constexpr double gravity = 800;
    static constexpr double floor = 80;
private:
    CS230::GameObjectManager gameobjectmanager;
    Cat* cat_ptr = nullptr;
    std::vector<Asteroid*> asteroids;
    CS230::Camera camera;
    Background background;
    Math::vec2 cat_position;


    static constexpr double cat_speed = 140;
};