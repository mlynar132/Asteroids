#include <iostream>

#include "Game.h"
#undef main // this fixes: Error	LNK2019	unresolved external symbol SDL_main referenced in function main_getcmdline	test1	C : \Work\Programming\C++\SDL\test1\test1\SDL2main.lib(SDL_windows_main.obj)	1

Game* Game = nullptr;

int main(int argc, const char* argv[])
{
    const bool PrintPerformance = true;
    const bool CapFPS = true;
    const int FPS = 60;
    const int FPSWorse = 30;
    const int FrameDelay = 1000 / FPS;
    const int FrameDelayWorse = 1000 / FPSWorse;
    const int Width = 800;
    const int Height = 800;
    Uint32 FrameStart; //time at beginning of frame
    Uint32 FrameTime = 0; //time after events update render etc.
    Uint32 LastFrame = SDL_GetTicks();

    Game = new class Game();
    Game->Init("DupaEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, false);

    while (Game->Running())
    {
        FrameStart = SDL_GetTicks();

        LastFrame = FrameStart;

        Game->HandleEvents();
        Game->Update();
        Game->Render();
        FrameTime = SDL_GetTicks() - FrameStart;
        if (CapFPS)
        {
            if (FrameDelay > FrameTime)
            {
                if (PrintPerformance)
                {
                    std::cout << FrameDelay - FrameTime << " millisecond before the time for next frame\n";
                }
                SDL_Delay(FrameDelay - FrameTime);
            }
            else if (FrameDelayWorse > FrameTime)
            {
                if (PrintPerformance)
                {
                    std::cout << "oh no we went bellow 60 frames per second\n";
                }
                SDL_Delay(FrameDelayWorse - FrameTime);
            }
            else
            {
                if (PrintPerformance)
                {
                    std::cout <<
                        "DEATH DEATH YOU FAILED OPTIMIZING THIS SHIT. or the PC that's running this is worse than mine :)\n";
                    Game::CloseGame = true;
                }
            }
        }
        else
        {
            //redo the code for Update with delta time
            //std::cout <<  static_cast<float>(FrameTime) * 0.001f << " " << 1.0f / static_cast<float>(FrameTime) * 0.001f << "Frames per second\n";
        }
    }

    Game->Clean();

    return 0;
}
