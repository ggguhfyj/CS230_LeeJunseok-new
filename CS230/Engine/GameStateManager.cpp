/*
Copyright(C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name : GameStateManager.cpp
Project : CS230 Engine
Author : Junseok Lee
Created:    March 8, 2023
Updated:		March 18, 2025
*/

#include "GameStateManager.h"
#include "Engine.h"

CS230::GameStateManager::GameStateManager() :
    current_gamestate(nullptr),
    next_gamestate(nullptr),
    status(Status::STARTING)
{ }
void CS230::GameStateManager::AddGameState(GameState& gamestate) {
    gamestates.push_back(&gamestate);
}
void CS230::GameStateManager::SetNextGameState(int index) {
    next_gamestate = gamestates[index];
}
void CS230::GameStateManager::ReloadState() {
    status = Status::UNLOADING;
}
void CS230::GameStateManager::ClearNextGameState() {
    next_gamestate = nullptr;
}
bool CS230::GameStateManager::HasGameEnded() {
    return status == Status::EXIT;
}
void Engine::Start(std::string window_title) {
    logger.LogEvent("Engine Started");
    window.Start(window_title);
    //Start other services
    last_test = last_tick;
}
void CS230::GameStateManager::Update([[maybe_unused]] double dt) {
    switch (status) {
    case Status::STARTING:
        if (gamestates.size() >= 1) {
            next_gamestate = gamestates[0];
            status = Status::LOADING;
        }
        else status = Status::STOPPING;
        break;
    case Status::LOADING:
        current_gamestate = next_gamestate;
        Engine::GetLogger().LogEvent("Load " + current_gamestate->GetName());
        current_gamestate->Load();
        Engine::GetLogger().LogEvent("Load Complete");
        status = Status::UPDATING;
        break;
    case Status::UPDATING:
        if (current_gamestate != next_gamestate) {// if there is a change in game states
            status = Status::UNLOADING;
        }
        else {
            Engine::GetLogger().LogVerbose("Update " + current_gamestate->GetName());
            current_gamestate->Update(dt);
            current_gamestate->Draw();
        }
        break;
    case Status::UNLOADING:
        Engine::GetLogger().LogVerbose("Unload " + current_gamestate->GetName());
        current_gamestate->Unload();
        Engine::GetLogger().LogVerbose("Unload Complete");
        status = (next_gamestate == nullptr) ? Status::STOPPING : Status::LOADING;
        break;
    case Status::STOPPING:
        status = Status::EXIT;
        break;
    case Status::EXIT:
        break;
    }
}