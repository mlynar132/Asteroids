#pragma once

#include "GameObject.h"

class Asteroid : public GameObject
{
public:
    Asteroid(vec2df location, vec2df direction, int r, float speed, const char* fileName);
    ~Asteroid();

    void Update() override;
    void Render() override;
    void OnCollision(GameObject* other) override;

    float Speed;

private:
    void Bounce(Asteroid* other);
    SDL_Texture* Tex;
};
