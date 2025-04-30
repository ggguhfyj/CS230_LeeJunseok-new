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
//testing for new branch
Cat::Cat(Math::vec2 start_position, const CS230::Camera& camera) :
    start_position(start_position),
    position(start_position),
    camera(camera)
{

}

void Cat::Load() {
    sprite.Load("Assets/Cat.spt");
    position = start_position;
    velocity = { 0, 0 };
    current_state = &state_idle;
    current_state->Enter(this);
}


void Cat::Update(double dt) {
    current_state->Update(this, dt);
    //position += velocity * dt;
    current_state->CheckExit(this);

    // Boundary Check
    if (position.x < camera.GetPosition().x + sprite.GetFrameSize().x / 2) {
        position.x = camera.GetPosition().x + sprite.GetFrameSize().x / 2;
        velocity.x = 0;
    }
    if (position.x + sprite.GetFrameSize().x / 2 > camera.GetPosition().x + Engine::GetWindow().GetSize().x) {
        position.x = camera.GetPosition().x + Engine::GetWindow().GetSize().x - sprite.GetFrameSize().x / 2;
        velocity.x = 0;
    }
    object_matrix = Math::TranslationMatrix(position);
    if (flipped == true) {
        object_matrix *= Math::ScaleMatrix({ -1.0, 1.0 });
    }
}



void Cat::update_x_velocity(double dt) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        velocity.x += x_acceleration * dt;
        if (velocity.x > max_velocity) {
            velocity.x = max_velocity;
            Engine::GetLogger().LogEvent("Reached max velocity while moving Right\n");
        }
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
        velocity.x -= x_acceleration * dt;
        if (velocity.x < -max_velocity) {
            velocity.x = -max_velocity;
            Engine::GetLogger().LogEvent("Reached max velocity while moving left\n");
        }
    }
    else {
        if (velocity.x > x_drag * dt) {
            velocity.x -= x_drag * dt;
        }
        else if (velocity.x < -x_drag * dt) {
            velocity.x += x_drag * dt;
        }
        else {
            velocity.x = 0;
        }
    }
}

void Cat::change_state(State* new_state) {
    Engine::GetLogger().LogDebug("Cat Leaving State: " + current_state->GetName());
    Engine::GetLogger().LogDebug("Cat Entering State: " + new_state->GetName());
    current_state = new_state;
    current_state->Enter(this);
}

void Cat::Draw(Math::TransformationMatrix camera_matrix)
{
    sprite.Draw(camera_matrix * object_matrix);
}

void Cat::State_Jumping::Enter(Cat* cat) {
    cat->velocity.y = Cat::jump_velocity;
}
void Cat::State_Jumping::Update(Cat* cat, double dt) {
    cat->velocity.y -= Mode1::gravity * dt;
    cat->update_x_velocity(dt);
    cat->position += cat->velocity * dt;
}
void Cat::State_Jumping::CheckExit(Cat* cat) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up) == false) {
        cat->change_state(&cat->state_falling);
        cat->velocity.y = 0;
    }
    else if (cat->velocity.y <= 0) {
        cat->change_state(&cat->state_falling);
    }
}


void Cat::State_Idle::Enter([[maybe_unused]] Cat* cat) {}
void Cat::State_Idle::Update([[maybe_unused]] Cat* cat, [[maybe_unused]] double dt) {}
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
}

void Cat::State_Falling::Update(Cat* cat, double dt) {
    cat->velocity.y -= Mode1::gravity * dt;
    cat->update_x_velocity(dt);
    cat->position += cat->velocity * dt;
}

void Cat::State_Falling::CheckExit(Cat* cat) {
    if (cat->position.y <= Mode1::floor) {
        cat->position.y = Mode1::floor;
        cat->velocity.y = 0;
        if (cat->velocity.x == 0) {
            cat->change_state(&cat->state_idle);
        }
        else {
            bool moving_right = cat->velocity.x > 0;
            bool right_down = Engine::GetInput().KeyDown(CS230::Input::Keys::Right);
            bool left_down = Engine::GetInput().KeyDown(CS230::Input::Keys::Left);
            if ((moving_right && right_down) || (!moving_right && left_down)) {
                cat->change_state(&cat->state_running);
            }
            else {
                cat->change_state(&cat->state_skidding);
            }
        }
    }
}

void Cat::State_Running::Enter(Cat* cat) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        cat->flipped = false;
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
        cat->flipped = true;
    }
}

void Cat::State_Running::Update(Cat* cat, double dt) {
    cat->update_x_velocity(dt);
    cat->position += cat->velocity * dt;
}

void Cat::State_Running::CheckExit(Cat* cat) {
    if (cat->velocity.x == 0) {
        cat->change_state(&cat->state_idle);
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
        cat->change_state(&cat->state_jumping);
    }
    else {
        bool moving_right = cat->velocity.x > 0;
        bool right_down = Engine::GetInput().KeyDown(CS230::Input::Keys::Right);
        bool left_down = Engine::GetInput().KeyDown(CS230::Input::Keys::Left);
        if ((moving_right && left_down) || (!moving_right && right_down)) {
            cat->change_state(&cat->state_skidding);
        }
    }
}

void Cat::State_Skidding::Enter([[maybe_unused]] Cat* cat) {
}

void Cat::State_Skidding::Update(Cat* cat, double dt) {
    if (cat->velocity.x > 0) {
        cat->velocity.x -= (Cat::x_drag + Cat::x_acceleration) * dt;
        if (cat->velocity.x < 0) cat->velocity.x = 0;
    }
    else if (cat->velocity.x < 0) {
        cat->velocity.x += (Cat::x_drag + Cat::x_acceleration) * dt;
        if (cat->velocity.x > 0) cat->velocity.x = 0;
    }
    cat->position += cat->velocity * dt;
}

void Cat::State_Skidding::CheckExit(Cat* cat) {
    if (cat->velocity.x == 0) {
        cat->change_state(&cat->state_idle);
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
        cat->change_state(&cat->state_jumping);
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left) || Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        cat->change_state(&cat->state_running);
    }
}