#include <iostream>

#include "Game.h"
#undef main // this fixes: Error	LNK2019	unresolved external symbol SDL_main referenced in function main_getcmdline	test1	C : \Work\Programming\C++\SDL\test1\test1\SDL2main.lib(SDL_windows_main.obj)	1



Game* Game = nullptr;

int main(int argc, const char* argv[])
{
    const bool PrintPerformance = false;
    const bool CapFPS = true;
    const int FPS = 60;
    const int FPSWorse = 30;
    const int FrameDelay = 1000 / FPS;
    const int FrameDelayWorse = 1000 / FPSWorse;
    Uint32 FrameStart; //time at beginning of frame
    Uint32 FrameTime = 0; //time after events update render etc.
    Uint32 LastFrame = SDL_GetTicks();

    Game = new class Game();
    Game->Init("DupaEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false);

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
                }
            }
        }
        else
        {
            //std::cout <<  static_cast<float>(FrameTime) * 0.001f << " " << 1.0f / static_cast<float>(FrameTime) * 0.001f << "Frames per second\n";
        }
    }

    Game->Clean();

    return 0;
}


/*#include "SDL.h"
#undef main
#include <iostream>


//don't do this, this is just an example
SDL_Renderer* renderer;
SDL_Window* window;
bool isRunning;
bool fullscreen;
void handleEvents();
void update();
void render();


//please don't put all your code in main like I did.
int main() {

	fullscreen = false;
	int flags = 0;
	flags = SDL_WINDOW_RESIZABLE;
	if (fullscreen) {
		flags = flags | SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized!\n";

		window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, flags);
		if (window) {
			std::cout << "Window Created!\n";
			SDL_SetWindowMinimumSize(window, 100, 100);
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 121, 121, 121, 255);
			std::cout << "Renderer created!\n";
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			isRunning = true;
		}

	}

	while (isRunning) {
		handleEvents();
		update();
		render();
	}

	//frees memory associated with renderer and window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);	//error here
	SDL_Quit();


	return 0;
}

//handles any events that SDL noticed.
void handleEvents() {
	//the only event we'll check is the  SDL_QUIT event.
	SDL_Event event;
	SDL_PollEvent(&event);


	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

//simple render function
void render() {
	SDL_SetRenderDrawColor(renderer, 121, 121, 121, 255);
	SDL_RenderClear(renderer);

	//your stuff to render would typically go here.
	SDL_RenderPresent(renderer);
}

//simple update function
void update() {
	//if things could update the code would go in here.
}*/
