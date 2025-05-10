/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  crate.h
Project:    CS230 Engine
Author:     Jonathan Holmes, junseok lee
Created:    March 24, 2025
Updated:    sometime in may, 2025
*/

#pragma once
#include "..\Engine\GameObject.h"

class Crates : public CS230::GameObject {
public:
    Crates(Math::vec2 position, int size);
};
