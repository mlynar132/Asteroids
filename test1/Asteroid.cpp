#include "Asteroid.h"

#include <iostream>

#include "Bullet.h"
#include "Game.h"
#include "HelpLibrary.h"
#include "Ship.h"

Asteroid::Asteroid(vec2df location, vec2df direction, int r, float speed, const char* fileName)
    : GameObject(location, direction, r, fileName), Speed(speed)
{
}

Asteroid::~Asteroid()
{
}

void Asteroid::Update()
{
    GameObject::Update();
    Location += Direction * Speed;
    if (Location.x + Radius <= 0 || Location.x >= Game::Width + Radius ||
        Location.y + Radius <= 0 || Location.y >= Game::Height + Radius)
    {
        //bIsDead = true;
    }
}

void Asteroid::Render()
{
    GameObject::Render();
}

void Asteroid::OnCollision(GameObject* other)
{
    GameObject::OnCollision(other);
    if (Bullet* bullet = dynamic_cast<Bullet*>(other))
    {
        bIsDead = true;
    }
    else if (Asteroid* asteroid = dynamic_cast<Asteroid*>(other))
    {
        //bounce
        if (!Game::StressTestingMode)
        {
            Bounce(asteroid);
            //bIsDead = true;
        }
    }
    else if (Ship* ship = dynamic_cast<Ship*>(other))
    {
        bIsDead = true;
    }
}

void Asteroid::Bounce(Asteroid* other)
{
    // Direction *= Speed;
    // Direction += other->Direction * other->Speed;
    // Direction = Direction * Speed + other->Direction * other->Speed;
    
    Direction.Normalize();
}
