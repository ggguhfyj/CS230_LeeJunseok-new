#include "../Game/Asteroid.h"
#include "Mode1.h"
#include "../Engine/Engine.h"
Asteroid::Asteroid()
{
}
Asteroid::Asteroid(Math::vec2 start_position):start_position(start_position),position(start_position)
{
    velocity = { 0.0,0.0 };
}

void Asteroid::Load()
{
    
    position = start_position;
    velocity = {0,0};
    sprite.Load("Assets/Asteroid.spt");
    current_state = &state_bouncing;
    current_state->Enter(this);

}

void Asteroid::Update(double dt) {
    

    current_state->Update(this, dt);
    
    current_state->CheckExit(this);

    if (position.y < Mode1::floor) {
        position.y = Mode1::floor;
        velocity.y = bounce_velocity;
    }
    object_matrix = Math::TranslationMatrix(position);
}


void Asteroid::Draw(Math::TransformationMatrix camera_matrix)
{
    sprite.Draw(camera_matrix * object_matrix);

}


void Asteroid::change_state(State* new_state)
{
    current_state = new_state;
    current_state->Enter(this);
}

void Asteroid::State_Bouncing::Enter(Asteroid* asteroid)
{
    asteroid->velocity.y = bounce_velocity;
}

void Asteroid::State_Bouncing::Update(Asteroid* asteroid, double dt)
{
    asteroid->velocity.y -= Mode1::gravity * dt;
    asteroid->position += asteroid->velocity * dt;
}

void Asteroid::State_Bouncing::CheckExit(Asteroid* asteroid)
{
    if (asteroid->position.y < Mode1::floor) {
        asteroid->change_state(&asteroid->state_landing);
    }
}

void Asteroid::State_Landing::Enter(Asteroid* asteroid)
{
    asteroid->velocity.y = 0;
    asteroid->position.y = Mode1::floor;
}

void Asteroid::State_Landing::Update(Asteroid* asteroid, double dt)
{
    dt; asteroid;
}

void Asteroid::State_Landing::CheckExit(Asteroid* asteroid)
{
    asteroid->change_state(&asteroid->state_bouncing);
}
