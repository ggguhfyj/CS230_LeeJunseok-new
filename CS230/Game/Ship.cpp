/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Cat.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes,JunSeok Lee
Created:    March 8, 2023
*/

#pragma once
#include "Ship.h"
#include "../Engine/Engine.h"

Ship::Ship(Math::vec2 start_position) :
    start_position(start_position),
    position(start_position),
    velocity({ 0.0, 0.0 })
{
}

void Ship::Load() {
    sprite.Load("Assets/Ship.spt");
    flame_left.Load("Assets/Flame.spt");
    flame_right.Load("Assets/Flame.spt");
    velocity = { 0, 0 };
    position = start_position;
    flame_is_on = false;
    drawflame = false;
    angle = 0.0;
}

void Ship::Update([[maybe_unused]] double dt) {
    bool IsWDown = Engine::GetInput().KeyDown(CS230::Input::Keys::W);
    if (IsWDown != flame_is_on) {
        flame_is_on = IsWDown;
        int anim = flame_is_on
            ? static_cast<int>(FlameAnim::Flame)
            : static_cast<int>(FlameAnim::None);

        flame_left.PlayAnimation(anim);
        flame_right.PlayAnimation(anim);
    }
    flame_right.Update(dt);
    flame_left.Update(dt);
    sprite.Update(dt);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
        drawflame = true;
        velocity += Math::RotationMatrix(angle) * Math::vec2{ 0, speed * dt };
    }

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        angle+= rotation_speed;
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        angle-= rotation_speed;
    }
    velocity -= velocity * drag * dt;

    Engine::GetLogger().LogDebug("Velocity: " + std::to_string(velocity.x) + ", " + std::to_string(velocity.y));

    position += velocity * dt;

    Math::ivec2 windowSize = Engine::GetWindow().GetSize();
    Math::ivec2 spriteSize = sprite.GetFrameSize();

    if (position.x < -spriteSize.x) {
        position.x = windowSize.x;

    }
    else if (position.x - spriteSize.x/2 > windowSize.x) {
        position.x = -spriteSize.x;
    }

    if (position.y < -spriteSize.y) {
        position.y = windowSize.y;
    }
    else if (position.y - spriteSize.y / 2 > windowSize.y) {
        position.y = -spriteSize.y;
    }
    object_matrix = Math::TranslationMatrix(position) * Math::RotationMatrix(angle) * Math::ScaleMatrix(scale);
}

void Ship::Draw() {
    if (drawflame)
    {
        flame_left.Draw(object_matrix * Math::TranslationMatrix(static_cast<Math::vec2>(sprite.GetHotSpot(1))));
        flame_right.Draw(object_matrix * Math::TranslationMatrix(static_cast<Math::vec2>(sprite.GetHotSpot(2))));
    }
    
    sprite.Draw(object_matrix);
}


void Ship::Reset() {
    position = start_position;
    velocity = { 0.0, 0.0 };
}