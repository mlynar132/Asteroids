#include "Game.h"

#include "Asteroid.h"
#include "iostream"
#include "ObjectManager.h"
#include "Ship.h"

SDL_Renderer* Game::renderer = nullptr;
int Game::Width = 0;
int Game::Height = 0;
int Game::Score = 0;
int Game::Hits = 0;

bool Game::StressTestingMode = false;
bool Game::Invincible = true;


Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    Width = width;
    Height = height;
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialized!...\n";

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << "window created!\n";
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            std::cout << "renderer created\n";
        }
        Player = dynamic_cast<Ship*>(ObjectManager::GetInstance()->SpawnObject(new Ship{
            vec2df(300.0f, 300.0f), vec2df(1.0f, 0.0f), 16, "Assets/Player.png"
        }));
        bIsRunning = true;
    }
    else
    {
        bIsRunning = false;
    }
}

void Game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        bIsRunning = false;
        break;
    default:
        break;
    }
}

void Game::Update()
{
    ObjectManager::GetInstance()->UpdateObjects();
    if (TickCounter >= 60)
    {
        SpawnWave(SpawnAmount);
        SpawnAmount *= 2;
        TickCounter = 0;
    }
    else
    {
        TickCounter++;
    }
    std::cout << ObjectManager::GetInstance()->ObjectAmount() << '\n';
    // if (ObjectManager::GetInstance()->CheckForGameOver())
    // {
    //     Game::Clean();
    // }
}

void Game::Render()
{
    SDL_RenderClear(renderer);
    ObjectManager::GetInstance()->RenderObjects();
    SDL_RenderPresent(renderer);
}

void Game::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "GAME CLEANED\n";
}

void Game::SpawnWave(int amount)
{
    //make a check to not spawn near player
    const int SafeDistance = 100;

    for (int i = 0; i < amount; ++i)
    {
        vec2df loc(static_cast<float>(rand() % Game::Width), static_cast<float>(rand() % Game::Height));
        int Radius = (rand() % 5 + 1) * 16; //5 different sizes
        float angle = static_cast<float>(rand() % 360);
        vec2df dir(0.0f, 0.0f);
        dir = dir.AngleDegToDirection(angle);
        float speed = static_cast<float>(rand() % 5 + 1);
        while (static_cast<float>(Player->Radius + Radius + SafeDistance) >=
            Player->Location.DistanceTo(loc))
        {
            loc.x = static_cast<float>(rand() % Game::Width);
            loc.y = static_cast<float>(rand() % Game::Height);
        }

        ObjectManager::GetInstance()->SpawnObject(new Asteroid{
            vec2df(loc), vec2df(dir), Radius, speed, "Assets/Asteroid.png"
        });
    }
}
