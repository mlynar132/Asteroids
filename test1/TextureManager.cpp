#include "TextureManager.h"
#include "Game.h"
#include <SDL_image.h>

std::map<const char*, SDL_Texture*> TextureManager::LoadedTextures = std::map<const char*, SDL_Texture*>();

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	if (LoadedTextures.count(fileName) != 0)
	{
		return LoadedTextures[fileName];
	}
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	LoadedTextures.insert(std::pair<const char*, SDL_Texture*>(fileName,tex));
	return tex;
}	
