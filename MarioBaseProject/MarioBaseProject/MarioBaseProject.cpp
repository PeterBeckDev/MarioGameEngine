#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <iostream>

#include "constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"
#include "SoundManager.h"

#include <SDL_mixer.h>

using namespace std;

//globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager;
SoundManager* g_sound_manager;
Uint32 g_old_time;


//function prototypes
bool InitSDL();
void CLoseSDL();
bool Update();
void Render();
void LoadMusic(std::string path);
void LoadChunk(std::string path);

int main(int argc, char* args[])
{
	//check if SDL was setup correctily
	if (InitSDL())
	{

		


		g_sound_manager = new SoundManager();
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_INTRO,g_sound_manager);
		//set the time
		g_old_time = SDL_GetTicks();
		//flag to check if we wish to quit
		bool quit = false;

		//Game Loop
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}

	CLoseSDL();
	return 0;
}

bool InitSDL()
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SLD did not initialise. Error: " << SDL_GetError();
	}
	else
	{
		//setup passsed so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_renderer != nullptr)
		{
			//init PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initiaise, Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Rendere could not initialise. Error: " << SDL_GetError();
			return false;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mixer could not init. Error: " << Mix_GetError();
			return false;
		}
			
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not createrd. Error: " << SDL_GetError();
			return false;
		}

		if (TTF_Init() == -1)
		{
			cout << "TTF not initialised. Error: " << TTF_GetError();
			return false;
		}

		return true;
	}
}
void CLoseSDL()
{
	//clear the gamemanager
	delete game_screen_manager;
	game_screen_manager = nullptr;

	delete g_sound_manager;
	g_sound_manager = nullptr;
	//release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	//quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
bool Update()
{
	Uint32 new_time = SDL_GetTicks();

	//Event handle
	SDL_Event e;
	
	//get events
	SDL_PollEvent(&e);

	//handle the events
	switch (e.type)
	{
		//click the X to quit
	case SDL_QUIT:
		return true;
		break;
	}
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_sound_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
	return false;
}
void Render()
{
	//clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();
	
	SDL_RenderPresent(g_renderer);
}
