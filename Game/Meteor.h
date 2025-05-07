/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Meteor.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junseok Lee
Created:    April 30, 2025
Updated:    April 30, 2025
*/







#include<cmath>


#include"../Engine/GameObject.h"
class Meteor : public CS230::GameObject {
public:
    Meteor(Math::vec2 Window_Size);
    void Update(double dt) override;
private:
    Math::vec2 Window_Size;
    static constexpr double default_velocity = 100;// as done in the video
};
