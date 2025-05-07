
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.cpp
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 8, 2023
*/

#include "../Engine/Engine.h"
#include "States.h"
#include "Mode2.h"
#include "../Engine/Window.h"


Mode2::Mode2() : ship({ static_cast<double>(GetScreenWidth()) / 2 , static_cast<double>(GetScreenHeight()) / 2 }) // how to get the static constexpr from window.h using Get size and Engine Get window?
{
}   

void Mode2::Load() {
   double window_width = GetScreenWidth();
   double window_height = GetScreenHeight();
    //ship.Load();
    gameobjectmanager.Add(new Ship({ static_cast<double>(GetScreenWidth()) / 2 , static_cast<double>(GetScreenHeight()) / 2 }));
    gameobjectmanager.Add(new Meteor({ window_width, window_height }));
    gameobjectmanager.Add(new Meteor({ window_width, window_height }));
    gameobjectmanager.Add(new Meteor({ window_width, window_height }));
    gameobjectmanager.Add(new Meteor({ window_width, window_height }));
    gameobjectmanager.Add(new Meteor({ window_width, window_height }));

}


    void Mode2::Draw() {
        Engine::GetWindow().Clear(0x000000FF);
        gameobjectmanager.DrawAll(Math::TransformationMatrix());
       // gameobjectmanager.DrawAll(camera.GetMatrix());
    }

    void Mode2::Update([[maybe_unused]] double dt) {
        gameobjectmanager.UpdateAll(dt);
        if (IsKeyPressed(KEY_TWO)) {
            Engine::GetGameStateManager().ClearNextGameState();
            //Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode2));
        }
        if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
            Engine::GetGameStateManager().ReloadState();
        }


    }

    void Mode2::Unload() {

    }

