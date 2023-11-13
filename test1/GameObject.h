#pragma once

#include <SDL.h>
#include "HelpLibrary.h"
#include <vector>
#define PI 3.14159265f

// struct vec2df;

class GameObject
{
public:
    GameObject(vec2df location, vec2df direction, int r, const char* fileName);
    ~GameObject();

    bool operator==(const GameObject &other) const
    { return (Location == other.Location
              && Direction == other.Direction
              && Radius == other.Radius
              && bIsDead == other.bIsDead);
    }

 

    
    virtual void Update();
    virtual void Render();

    virtual void OnCollision(GameObject* other);

    bool bIsDead = false; //marking for removal

    vec2df Location;
    vec2df Direction = vec2df(1.0f, 2.0f); //by default look to the right
    float DiretionToAngleDeg()
    {
        return atan2(Direction.y, Direction.x) * 180.0f / PI;
    };
    int Radius;
    SDL_Rect DestRect;
private:
    SDL_Texture* Tex;
};

// hashing
 template <>
 struct std::hash<GameObject>
 {
     std::size_t operator()(const GameObject& o) const
     {
         using std::size_t;
         using std::hash;
         
         std::size_t seed = 17;
         seed = seed * 31 + hash<vec2df>()(o.Location);
         seed = seed * 31 + hash<vec2df>()(o.Direction);
         seed = seed * 31 + hash<int>()(o.Radius);
         seed = seed * 31 + hash<bool>()(o.bIsDead);
         return seed;
     }
 };