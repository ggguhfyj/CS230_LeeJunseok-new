/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Cat.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/
#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\Camera.h"
#include "..\Engine\Matrix.h"
class Cat {
public:
    Cat(Math::vec2 start_position,const CS230::Camera& camera);
    void Load();
    void Update(double dt);
    void Draw(Math::TransformationMatrix camera_matrix);

    const Math::vec2& GetPosition() const { return position; }; // public getter function;

private:
    void update_x_velocity(double dt);
    class State {
    public:
        virtual void Enter(Cat* cat) = 0;
        virtual void Update(Cat* cat, double dt) = 0;
        virtual void CheckExit(Cat* cat) = 0;
        virtual std::string GetName() = 0;
    };
    class State_Jumping : public State {
    public:
        virtual void Enter(Cat* cat) override;
        virtual void Update(Cat* cat, double dt) override;
        virtual void CheckExit(Cat* cat) override;
        std::string GetName() override { return "Jumping"; }
    };
    State_Jumping state_jumping;

    class State_Idle : public State {
    public:
        virtual void Enter(Cat* cat) override;
        virtual void Update(Cat* cat, double dt) override;
        virtual void CheckExit(Cat* cat) override;
        std::string GetName() override { return "Idle"; }
    };
    State_Idle state_idle;

    class State_Falling : public State {
    public:
        virtual void Enter(Cat* cat) override;
        virtual void Update(Cat* cat, double dt) override;
        virtual void CheckExit(Cat* cat) override;
        std::string GetName() override { return "Falling"; }
    };
    State_Falling state_falling;
    class State_Running : public State {
    public:
        virtual void Enter(Cat* cat) override;
        virtual void Update(Cat* cat, double dt) override;
        virtual void CheckExit(Cat* cat) override;
        std::string GetName() override { return "Running"; }
    };
    State_Running state_running;

    class State_Skidding : public State {
    public:
        virtual void Enter(Cat* cat) override;
        virtual void Update(Cat* cat, double dt) override;
        virtual void CheckExit(Cat* cat) override;
        std::string GetName() override { return "Skidding"; }
    };
    State_Skidding state_skidding;


    void change_state(State* new_state);
    State* current_state = nullptr;
    CS230::Sprite sprite;
    Math::vec2 start_position;
    Math::vec2 position;
    Math::vec2 velocity;
    const CS230::Camera& camera;
    Math::TransformationMatrix object_matrix;
    static constexpr double x_acceleration = 300;
    static constexpr double x_drag = 200;
    static constexpr double max_velocity = 250;
    static constexpr double jump_velocity = 650;
    
    bool flipped = false;
    bool jumping = false;
    bool going_up = false;
};