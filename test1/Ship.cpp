#include "Ship.h"

#include <iostream>
#include <algorithm>

#include "Asteroid.h"
#include "Bullet.h"
#include "Game.h"
#include "HelpLibrary.h"
#include "ObjectManager.h"

Ship::Ship(vec2df location, vec2df direction, int r, const char* fileName)
    : GameObject(location, direction, r, fileName)
{
    HP = MaxHP;
}

Ship::~Ship()
{
}

void Ship::Update()
{
    GameObject::Update();
    const Uint8* state = SDL_GetKeyboardState(NULL);
    vec2df dir(0.0f, 0.0f);
    if (state[SDL_SCANCODE_A])
    {
        Direction.RotateByDeg(RotationSpeendDeg * -1.0f);
    }
    if (state[SDL_SCANCODE_D])
    {
        Direction.RotateByDeg(RotationSpeendDeg * 1.0f);
    }
    if (state[SDL_SCANCODE_W])
    {
        Location += Direction * Speed;
    }
    if (state[SDL_SCANCODE_S])
    {
        Location -= Direction * Speed;
    }
    if (state[SDL_SCANCODE_SPACE] && !bIsShootingPressed)
    {
        Shoot();
        bIsShootingPressed = true;
    }
    if (!state[SDL_SCANCODE_SPACE] && bIsShootingPressed)
    {
        bIsShootingPressed = false;
    }
    Location.x = SDL_clamp(Location.x, static_cast<float>(0 + Radius), static_cast<float>(Game::Width - Radius));
    Location.y = SDL_clamp(Location.y, static_cast<float>(0 + Radius), static_cast<float>(Game::Height - Radius));
}

void Ship::Render()
{
    GameObject::Render();
}

void Ship::OnCollision(GameObject* other)
{
    GameObject::OnCollision(other);

    if (Asteroid* asteroid = dynamic_cast<Asteroid*>(other))
    {
        TakeDamage();
    }
}

void Ship::Shoot()
{
    ObjectManager::GetInstance()->SpawnObject(new Bullet{
        vec2df(Location.x + Direction.x * (Radius + BulletRadius), Location.y + Direction.y * (Radius + BulletRadius)),
        vec2df(Direction), BulletRadius, "Assets/Bullet.png"
    });
}

void Ship::TakeDamage()
{
    if (Game::Invincible || Game::StressTestingMode)
    {
        return; 
    }
    HP--;
    if (HP <= 0)
    {
        bIsDead = true;
    }
}
