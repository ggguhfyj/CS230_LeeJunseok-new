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


#include "Crates.h"
#include "../Engine/Engine.h"
#include "../Game/Mode1.h"
#include <cmath>

Crates::Crates(Math::vec2 position, int size) : CS230::GameObject(position) {
    switch (size) {
    case 1:
        sprite.Load("Assets/Crates1.spt");
        break;
    case 2:
        sprite.Load("Assets/Crates2.spt");
        break;
    case 3:
        sprite.Load("Assets/Crates3.spt");
        break;
    case 5:
        sprite.Load("Assets/Crates5.spt");
        break;
    }
}
