/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Cat.cpp
Project:    CS230 Engine
Author:     JunSeok lee
Created:    March 8, 2023
*/

#pragma once
#include "Cat.h"
#include "../Engine/Engine.h"
#include "../Game/Mode1.h"
#include <cmath>

Cat::Cat(Math::vec2 start_position, const CS230::Camera& camera) :
    //start_position(start_position),
    //velocity({ 0.0,0.0 }),
    //position(start_position),
    camera(camera),
    current_state(&state_idle)
    //flipped(false)
    
{
    
    start_position;
    sprite.Load("Assets/Cat.spt");
    current_state->Enter(this);
    
}

//void Cat::Load() {
//    sprite.Load("Assets/Cat.spt");
//    //position = start_position;
//    velocity = { 0, 0 };
//    current_state = &state_idle;
//    flipped = false;
//    current_state->Enter(this);
//}


void Cat::Update(double dt) {
    current_state->Update(this, dt);
    sprite.Update(dt);
    UpdatePosition(dt * GetVelocity());
    current_state->CheckExit(this);

    // Boundary Check
    if (GetPosition().x < camera.GetPosition().x + sprite.GetFrameSize().x / 2) {
        SetPosition({ camera.GetPosition().x + sprite.GetFrameSize().x / 2, GetPosition().y });
        SetVelocity({ 0, GetVelocity().y });
    }
    if (GetPosition().x + sprite.GetFrameSize().x / 2 > camera.GetPosition().x + Engine::GetWindow().GetSize().x) {
        SetPosition({ camera.GetPosition().x + Engine::GetWindow().GetSize().x - sprite.GetFrameSize().x / 2, GetPosition().y });
        SetVelocity({ 0, GetVelocity().y });
    }
}



void Cat::update_x_velocity(double dt) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right) && !Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
        //velocity.x += x_acceleration * dt;
        this->UpdateVelocity({ x_acceleration * dt,0 });

        if (this->GetVelocity().x > max_velocity) {
            //velocity.x = max_velocity;
            this->SetVelocity({ max_velocity, this->GetVelocity().y });
            //Engine::GetLogger().LogEvent("Reached max velocity while moving Right\n");
        }
        //flipped = false;
        this->SetScale({1,1}); //assuming 1,1 is the normal scale
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left) && !Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        //velocity.x -= x_acceleration * dt;
        this->UpdateVelocity({ -x_acceleration * dt,0 });
        if (this->GetVelocity().x < -max_velocity) {
            this->SetVelocity({ -max_velocity, this->GetVelocity().y });
           // Engine::GetLogger().LogEvent("Reached max velocity while moving left\n");
        }
        this->SetScale({ -1,1 }); //assuming -1,1 is the inverted one
    }
    else {
        if (this->GetVelocity().x > x_drag * dt) {
            //velocity.x -= x_drag * dt;
            this->UpdateVelocity({ -x_drag * dt,0 });
        }
        else if (this->GetVelocity().x < -x_drag * dt) {
            //velocity.x += x_drag * dt;
            this->UpdateVelocity({x_drag * dt,0 });
        }
        else {
            //velocity.x = 0;
            this->SetVelocity({ 0,this->GetVelocity().y});
        }
    }
}

void Cat::change_state(State* new_state) {
    if (!current_state || !new_state) {
        Engine::GetLogger().LogError("null");
        return;
    }
    Engine::GetLogger().LogDebug("Cat Leaving State: " + current_state->GetName());
    Engine::GetLogger().LogDebug("Cat Entering State: " + new_state->GetName());
    current_state = new_state;
    current_state->Enter(this);
}

//void Cat::Draw(Math::TransformationMatrix camera_matrix)
//{
//    sprite.Draw(camera_matrix * object_matrix);
//}

void Cat::State_Jumping::Enter(Cat* cat) {
    cat->sprite.PlayAnimation(static_cast<int>(Animations::Jumping));
    //cat->velocity.y = Cat::jump_velocity;
    cat->SetVelocity({ cat->GetVelocity().x, Cat::jump_velocity });
}
void Cat::State_Jumping::Update(Cat* cat, double dt) {
    //cat->velocity.y -= Mode1::gravity * dt;
    cat->UpdateVelocity({ 0,-Mode1::gravity * dt });
    cat->update_x_velocity(dt);
    //cat->position += cat->velocity * dt;
    //cat->UpdatePosition({ cat->GetVelocity().x * dt,cat->GetVelocity().y * dt }); //CHANGE
}
void Cat::State_Jumping::CheckExit(Cat* cat) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up) == false) {
        //Engine::GetLogger().LogDebug("Released Jump Early : " + std::to_string(cat->position.y));
        cat->change_state(&cat->state_falling);
        //cat->velocity.y = 0;
        cat->SetVelocity({ cat->GetVelocity().x,0 });
    }
    else if (cat->GetVelocity().y <= 0) {
        cat->change_state(&cat->state_falling);
    }
}


void Cat::State_Idle::Enter([[maybe_unused]] Cat* cat) { 
    cat->sprite.PlayAnimation(static_cast<int>(Animations::Idle)); 
}
void Cat::State_Idle::Update([[maybe_unused]] Cat* cat, [[maybe_unused]] double dt) {
    if (cat->GetPosition().y > Mode1::floor) {
        //cat->GetVelocity().y -= Mode1::gravity * dt;
        cat->UpdateVelocity({ 0,Mode1::gravity * dt });
    }
    else {
        cat->SetVelocity({cat->GetVelocity().x, 0});
        //cat->position.y = Mode1::floor;
        cat->SetPosition({ cat->GetPosition().x,Mode1::floor });
    }
}
void Cat::State_Idle::CheckExit(Cat* cat) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
        cat->change_state(&cat->state_running);
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        cat->change_state(&cat->state_running);
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
        cat->change_state(&cat->state_jumping);
    }
}

void Cat::State_Falling::Enter([[maybe_unused]] Cat* cat) {
    cat->sprite.PlayAnimation(static_cast<int>(Animations::Falling));
}

void Cat::State_Falling::Update(Cat* cat, double dt) {
    //cat->velocity.y -= Mode1::gravity * dt;
    cat->UpdateVelocity({ 0,-Mode1::gravity * dt });
    cat->update_x_velocity(dt);
    //cat->position += cat->velocity * dt;
    //cat->UpdatePosition({ cat->GetVelocity().x * dt,cat->GetVelocity().y * dt });
}

void Cat::State_Falling::CheckExit(Cat* cat) {
    if (cat->GetPosition().y <= Mode1::floor) {
        //cat->position.y = Mode1::floor;
        cat->SetPosition({ cat->GetPosition().x,Mode1::floor });
        //cat->velocity.y = 0;
        cat->SetVelocity({ cat->GetVelocity().x, 0 });
        Engine::GetLogger().LogDebug("Landing: " + std::to_string(cat->GetPosition().y));

        if (std::abs(cat->GetVelocity().x) < 0.1) {
            cat->change_state(&cat->state_idle);
        }
        else {
            bool pressing_opposite = (cat->GetVelocity().x > 0 && Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) ||
                (cat->GetVelocity().x < 0 && Engine::GetInput().KeyDown(CS230::Input::Keys::Right));
            bool not_pressing_direction = !Engine::GetInput().KeyDown(CS230::Input::Keys::Left) && !Engine::GetInput().KeyDown(CS230::Input::Keys::Right);

            if (pressing_opposite || not_pressing_direction) {
                cat->change_state(&cat->state_skidding);
            }
            else {
                cat->change_state(&cat->state_running);
            }
        }
    }
}

void Cat::State_Running::Enter(Cat* cat) {
    cat->sprite.PlayAnimation(static_cast<int>(Animations::Running));
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        //cat->flipped = false;
        cat->SetScale({ 1,1 });
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
        //cat->flipped = true;
        cat->SetScale({ -1,1 });
    }
    
}

void Cat::State_Running::Update(Cat* cat, double dt) {
    cat->update_x_velocity(dt);
    //cat->position += cat->velocity * dt;
    //cat->UpdatePosition({ cat->GetVelocity().x * dt ,cat->GetVelocity().y * dt });
}

void Cat::State_Running::CheckExit(Cat* cat) {
    if (cat->GetVelocity().x == 0) {
        cat->change_state(&cat->state_idle);
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
        cat->change_state(&cat->state_jumping);
    }
    else {
        bool moving_right = cat->GetVelocity().x > 0;
        bool right_down = Engine::GetInput().KeyDown(CS230::Input::Keys::Right);
        bool left_down = Engine::GetInput().KeyDown(CS230::Input::Keys::Left);
        if ((moving_right && left_down) || (!moving_right && right_down)) {
            cat->change_state(&cat->state_skidding);
        }
    }
}

void Cat::State_Skidding::Enter([[maybe_unused]] Cat* cat) {
    cat->sprite.PlayAnimation(static_cast<int>(Animations::Skidding));
}

void Cat::State_Skidding::Update(Cat* cat, double dt) {
    if (cat->GetVelocity().x > 0) {
        //cat->velocity.x -= (Cat::x_drag + Cat::x_acceleration) * dt;
        cat->UpdateVelocity({ -(Cat::x_drag + Cat::x_acceleration) * dt,0 });
        if (cat->GetVelocity().x < 0) cat->SetVelocity({0,cat->GetVelocity().y});
    }
    else if (cat->GetVelocity().x < 0) {
        //cat->velocity.x += (Cat::x_drag + Cat::x_acceleration) * dt;
        //if (cat->velocity.x > 0) cat->velocity.x = 0;
        cat->UpdateVelocity({ +(Cat::x_drag + Cat::x_acceleration) * dt,0 });
        if (cat->GetVelocity().x > 0) cat->SetVelocity({ 0,cat->GetVelocity().y });
    }
    //cat->UpdatePosition({ cat->GetVelocity().x * dt ,cat->GetVelocity().y * dt });
}

void Cat::State_Skidding::CheckExit(Cat* cat) {
    if (cat->GetVelocity().x == 0) {
        cat->change_state(&cat->state_idle);
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
        cat->change_state(&cat->state_jumping);
    }
    /*else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left) || Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        cat->change_state(&cat->state_running);
    }*/
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Left) || Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Right)) {
        cat->change_state(&cat->state_running);
    }
}