/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Ship.h
Project:    CS230 Engine
Author:     Junseok lee
Created:    March 29, 2025
*/
#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\Window.h"
#include "..\Engine\Matrix.h"

class Ship {
public:
	Ship(Math::vec2 start_position);
	void Load();
	void Update(double dt);
	void Draw();
	void Reset();
private:
	CS230::Sprite sprite;
	CS230::Sprite flame_left;
	CS230::Sprite flame_right;
	Math::vec2 start_position;
	Math::vec2 position;
	Math::vec2 velocity;
	Math::TransformationMatrix object_matrix;
	static constexpr double Speed = 140;
	static constexpr double speed = 700;
	static constexpr double drag = 1;
	double angle = 0;
	static constexpr double rotation_speed = 0.06;
	static constexpr double scale = 0.75;

};