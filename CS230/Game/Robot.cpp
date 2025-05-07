/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  crate.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, junseok lee
Created:    March 24, 2025
Updated:    sometime in may, 2025
*/


#include "Robot.h"
#include "../Engine/Engine.h"
#include "../Game/Mode1.h"
#include <cmath>

Robot::Robot(Math::vec2 position) : CS230::GameObject(position) {
    
        sprite.Load("Assets/Robot.spt");
     
}
