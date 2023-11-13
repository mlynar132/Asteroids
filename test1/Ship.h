
#include "GameObject.h"

class Ship : public GameObject {

public:
    Ship(vec2df location, vec2df direction, int r, const char* fileName);
    ~Ship();

    void Update() override;
    void Render() override;

    void OnCollision(GameObject* other) override;

private:
    void Shoot();
    void TakeDamage();
    const float Speed = 3.0f;
    const float RotationSpeendDeg = 4.0f;
    const int BulletRadius = 4;
    const int MaxHP = 3;
    int HP;
    bool bIsShootingPressed = false;
    SDL_Texture* Tex;
};
