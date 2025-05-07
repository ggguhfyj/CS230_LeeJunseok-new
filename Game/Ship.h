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
//#include "..\Engine\Sprite.h"
//#include "..\Engine\Vec2.h"
#include "..\Engine\Input.h"
#include "..\Engine\Window.h"
#include "..\Engine\Matrix.h"
#include "..\Engine\GameObject.h"

class Ship: public CS230::GameObject {
public:
	Ship(Math::vec2 position);
	//void Load();
	void Update(double dt)override;
	void Draw(Math::TransformationMatrix camera_matrix)override;
	void Reset();
private:
	enum class FlameAnim {
		None,
		Flame
	};
	CS230::Sprite sprite;
	CS230::Sprite flame_left;
	CS230::Sprite flame_right;
	Math::vec2 start_position;
	Math::vec2 position;
	Math::vec2 velocity;
	Math::TransformationMatrix object_matrix;
	//static constexpr double Speed = 140;
	static constexpr double speed = 700;
	static constexpr double drag = 1;
	//double angle = 0;
	static constexpr double rotation_speed = 5;
	static constexpr double scale = 0.75;
	bool drawflame = false;
	bool flame_is_on = false;

};