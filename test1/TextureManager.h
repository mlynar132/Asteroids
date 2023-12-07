#pragma once

#include <SDL.h>
#include <map>

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName);

private:
	static std::map<const char*, SDL_Texture*> LoadedTextures;
};