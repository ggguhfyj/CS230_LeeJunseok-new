/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Asteroid.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
//#include "..\Engine\Sprite.h"
//#include "..\Engine\Vec2.h"
#include "..\Engine\Matrix.h"
#include "..\Engine\GameObject.h"
class Asteroid : public CS230::GameObject {
   
public:
    Asteroid();
    Asteroid(Math::vec2 start_position);
    //void Load();
    void Update(double dt) override;
    //void Draw(Math::TransformationMatrix camera_matrix) override;

private:
    enum class Animations {
        state_land,
        None
    };
    class State {
    public:
        virtual void Enter(Asteroid* asteroid) = 0;
        virtual void Update(Asteroid* asteroid, double dt) = 0;
        virtual void CheckExit(Asteroid* asteroid) = 0;
        virtual std::string GetName() = 0;
    };
    class State_Bouncing : public State {
    public:
        virtual void Enter(Asteroid* asteroid) override;
        virtual void Update(Asteroid* asteroid, double dt) override;
        virtual void CheckExit(Asteroid* asteroid) override;
        virtual std::string GetName() override { return "Bounding"; }
    };
    State_Bouncing state_bouncing;

    class State_Landing : public State {
    public:
        virtual void Enter(Asteroid* asteroid) override;
        virtual void Update(Asteroid* asteroid, double dt) override;
        virtual void CheckExit(Asteroid* asteroid) override;
        virtual std::string GetName() override { return "Bounding"; }
    };
    State_Landing state_landing;

    void change_state(State* new_state);

    State* current_state = nullptr;



    //CS230::Sprite sprite;
    //Math::vec2 start_position;
    //Math::vec2 position;
    //Math::vec2 velocity;
    //Math::TransformationMatrix object_matrix;
    static constexpr double bounce_velocity = 500;
    static constexpr double landing = 0.5;
};
