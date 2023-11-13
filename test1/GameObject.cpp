#include "GameObject.h"

#include "Game.h"
#include "TextureManager.h"

GameObject::GameObject(vec2df location, vec2df direction, int r, const char* fileName)
    : Location(location), Direction(direction), Radius(r)
{
    DestRect.x = static_cast<int>(Location.x - Radius);
    DestRect.y = static_cast<int>(Location.y - Radius);
    DestRect.w = Radius * 2;
    DestRect.h = Radius * 2;
    Tex = TextureManager::LoadTexture(fileName);
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
    //destRect.x += 1;
    //destRect.y += 1;
}

void GameObject::Render()
{
    DestRect.x = static_cast<int>(Location.x - Radius);
    DestRect.y = static_cast<int>(Location.y - Radius);
    SDL_SetTextureColorMod(Tex, 255, 255, 255);
    SDL_RenderCopyEx(Game::renderer, Tex, nullptr, &DestRect, DiretionToAngleDeg(), nullptr,
                     SDL_RendererFlip::SDL_FLIP_NONE);
    // SDL_RenderCopy(Game::renderer, Tex, nullptr, &DestRect);
}

void GameObject::OnCollision(GameObject* other)
{
}
