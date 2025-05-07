/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.h
Project:    CS230 Engine
Author:     Jonathan Holmes, junseok Lee
Created:    March 8, 2023
*/

#pragma once
#include "Sprite.h"

namespace Math { class TransformationMatrix; }

namespace CS230 {
    class GameObject;


    class State {
    public:
        virtual void Enter(GameObject* object) = 0;
        virtual void Update(GameObject* object, double dt) = 0;
        virtual void CheckExit(GameObject* object) = 0;
        virtual std::string GetName() = 0;
    };

    class GameObject {
    public:

        GameObject(Math::vec2 position);
        GameObject(Math::vec2 position, double rotation, Math::vec2 scale);
        virtual ~GameObject() {}

        virtual void Update(double dt);
        virtual void Draw(Math::TransformationMatrix camera_matrix);

        const Math::TransformationMatrix& GetMatrix();
        const Math::vec2& GetPosition() const;
        const Math::vec2& GetVelocity() const;
        const Math::vec2& GetScale() const;
        double GetRotation() const;
        void change_state(State* new_state);
    protected:
        void SetPosition(Math::vec2 new_position);
        void UpdatePosition(Math::vec2 delta);
        void SetVelocity(Math::vec2 new_position);
        void UpdateVelocity(Math::vec2 delta);
        void SetScale(Math::vec2 new_scale);
        void UpdateScale(Math::vec2 delta);
        void SetRotation(double new_rotation);
        void UpdateRotation(double delta);

        Sprite sprite;

    private:
        Math::TransformationMatrix object_matrix;
        double rotation;
        Math::vec2 scale = {1,1};
        Math::vec2 position;
        Math::vec2 velocity;
        State* current_state;
        class State_None : public State {// set as default
        public:
            void Enter(GameObject*) override {}
            void Update(GameObject*, double) override {}
            void CheckExit(GameObject*) override {}
            std::string GetName() { return ""; }
        };
        State_None state_none;
        

    };
    
}
