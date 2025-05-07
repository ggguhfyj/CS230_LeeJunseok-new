/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.cpp
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 11, 2025
Updated:        March 23, 2025
*/

#include "GameObject.h"

CS230::GameObject::GameObject()
{
}

CS230::GameObject::GameObject(Math::vec2 position) :
    GameObject(position, 0, { 1, 1 })
{
}

CS230::GameObject::GameObject(Math::vec2 position, double rotation, Math::vec2 scale) :
    velocity({ 0,0 }),
    position(position),
    scale(scale),
    rotation(rotation)
{
}

void CS230::GameObject::Update(double dt) {
    sprite.Update(dt);
    if (velocity.x != 0 || velocity.y != 0) {
        UpdatePosition(velocity * dt);
    }
}

void CS230::GameObject::Draw(Math::TransformationMatrix camera_matrix) {
    sprite.Draw(camera_matrix * GetMatrix());
}

const Math::TransformationMatrix& CS230::GameObject::GetMatrix() {
    object_matrix = Math::TranslationMatrix(position) * Math::RotationMatrix(rotation) * Math::ScaleMatrix(scale);
    return object_matrix;
}

const Math::vec2& CS230::GameObject::GetPosition() const
{
    return this->position;
    
}

const Math::vec2& CS230::GameObject::GetVelocity() const
{
    return this->velocity;
    // TODO: insert return statement here
}

const Math::vec2& CS230::GameObject::GetScale() const
{
    return this->scale;
    // TODO: insert return statement here
}

double CS230::GameObject::GetRotation() const
{

    return this->rotation;
}

void CS230::GameObject::SetPosition(Math::vec2 new_position) {
    position = new_position;
}

void CS230::GameObject::UpdatePosition(Math::vec2 delta) {
    position += delta;
}

void CS230::GameObject::SetVelocity(Math::vec2 new_position)
{
    this->velocity = new_position;
}

void CS230::GameObject::UpdateVelocity(Math::vec2 delta)
{
    this->velocity += delta;
}

void CS230::GameObject::SetScale(Math::vec2 new_scale)
{
    this->scale = new_scale;
}

void CS230::GameObject::UpdateScale(Math::vec2 delta)
{
    this->scale += delta;
}

void CS230::GameObject::SetRotation(double new_rotation)
{
    this->rotation = new_rotation;
}

void CS230::GameObject::UpdateRotation(double delta)
{
    this->rotation += delta;
}
