#pragma once

#include "GameObject.h"

class Bullet : public GameObject {

public:
	Bullet(vec2df location, vec2df direction, int r, const char* fileName);
	~Bullet();

	void Update() override;
	void Render() override;

	void OnCollision(GameObject* other) override;

	const float Speed = 4.0f;

	private:
	SDL_Texture* Tex;
};
