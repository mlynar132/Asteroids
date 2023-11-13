#pragma once

#include <SDL.h>
class Ship;
static int Width;
static int Height;

class Game
{
public:
    Game();
    ~Game();

    void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void HandleEvents();
    void Update();
    void Render();
    void Clean();

    bool Running() { return bIsRunning; }

    static SDL_Renderer* renderer;
    static int Width;
    static int Height;
    static int Score;
    static int Hits;
    static bool StressTestingMode;
    static bool Invincible;
    static bool CloseGame;
    //TODO: make is super big bump up the asteroid spawn rate turn of death and just save when the app goes bellow 60 and then 30 FPS.

private:
    int TickCounter = 0;
    float SpawnAmount = 25;
    float SpawnIncrease = 1.5f;
    int SpawnInterval = 300; // this is in frames
    void SpawnWave(int amount);
    bool bIsRunning;
    Ship* Player;
    SDL_Window* window;
};
