/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.cpp
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 11, 2025
Updated:        March 23, 2025
*/

#include "../Engine/Engine.h"
#include "States.h"
#include "Mode1.h"
#include "Cat.h"
#include "Asteroid.h"


Mode1::Mode1() :
    //cat({ 300, floor }, camera),
    camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } })
{
    //asteroids.push_back(Asteroid({ 600, floor }));
    //asteroids.push_back(Asteroid({ 1800, floor }));
    //asteroids.push_back(Asteroid({ 2400, floor }));
}


void Mode1::Load() {
    background.Add("Assets/Planets.png",0.25);
    background.Add("Assets/Ships.png", 0.5);
    background.Add("Assets/Foreground.png", 1);
    
    cat_ptr = new Cat({ 300, floor }, camera);
    gameobjectmanager.Add(cat_ptr);
    gameobjectmanager.Add(new Asteroid({ 600, floor }));
    gameobjectmanager.Add(new Asteroid({ 1800, floor }));
    gameobjectmanager.Add(new Asteroid({ 2400, floor }));
    //cat.Load();
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { background.GetSize().x - Engine::GetWindow().GetSize().x, background.GetSize().y - Engine::GetWindow().GetSize().y } });
    //for (auto& a : asteroids)
    //{
    //    a.Load();   
    //}
}

void Mode1::Update([[maybe_unused]] double dt) {
    gameobjectmanager.UpdateAll(dt);

    camera.Update(cat_ptr->GetPosition());
    

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Enter)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode2));
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
        Engine::GetGameStateManager().ReloadState();
    }
    
}

void Mode1::Draw() {
    Engine::GetWindow().Clear(0x000000FF);
    background.Draw(camera);
    gameobjectmanager.DrawAll(camera.GetMatrix());
    //Engine::GetLogger().LogEvent(" draw position : " + std::to_string(camera.GetPosition().x));
    
    

    //cat.Draw(camera.GetMatrix());
    //for (auto& a : asteroids)
    //{
    //    a.Draw(camera.GetMatrix());
    //}
}

void Mode1::Unload() {
    background.Unload();
    gameobjectmanager.Unload();
    cat_ptr = nullptr;
}


//void Mode1::Clear() {
//    Engine::GetWindow().Clear(0x000000FF);
//}