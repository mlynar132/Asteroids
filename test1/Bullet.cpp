#include "Bullet.h"

#include <iostream>

#include "Asteroid.h"
#include "Game.h"
#include "HelpLibrary.h"
#include "ObjectManager.h"

Bullet::Bullet(vec2df location, vec2df direction, int r, const char* fileName)
    : GameObject(location, direction, r, fileName)
{
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
    GameObject::Update();
    Location += Direction * Speed;
    if (Location.x + Radius <= 0 || Location.x >= Game::Width + Radius ||
        Location.y + Radius <= 0 || Location.y >= Game::Height + Radius)
    {
        bIsDead = true;
        std::cout << "Die\n";
    }
}

void Bullet::Render()
{
    GameObject::Render();
}

void Bullet::OnCollision(GameObject* other)
{
    GameObject::OnCollision(other);

    if (Asteroid* asteroid = dynamic_cast<Asteroid*>(other))
    {
        bIsDead = true;
    }
}
