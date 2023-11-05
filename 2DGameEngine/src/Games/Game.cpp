#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>
#include "../Loggers/Logger.h"
#include "../Core/ECS.h"

Game::Game() : 
	_isRunning{ false },
	WindowWidth{ 800 },
	WindowHeight{ 600 }
{
	Logger::Log("Game constructor called");
}

Game::~Game()
{
	Logger::Log("Game destructor called");
}

void Game::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Logger::Error("Error initializing SDL.");
		return;
	}
	WindowWidth = 800;
	WindowHeight = 600;
	 _window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WindowWidth,
		WindowHeight,
		SDL_WINDOW_BORDERLESS);
	if (!_window)
	{
		Logger::Error("Error creating SDL window.");
		return;
	}
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!_renderer)
	{
		Logger::Error("Error creating SDL renderer.");
		return;
	}
	//SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
	_isRunning = true;
}

void Game::Setup()
{

}

void Game::Run()
{
	Setup();
	while (_isRunning)
	{
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
			case SDL_QUIT:
				_isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
					_isRunning = false;
				break;
		}
	}
}

void Game::Update()
{
	auto delayTime = MILLISECS_PER_FRAME - (SDL_GetTicks() - _millisecsPreviousFrame);
	if (delayTime > 0 && delayTime <= MILLISECS_PER_FRAME)
	{
		SDL_Delay(delayTime);
	}
	auto deltaTime = (SDL_GetTicks() - _millisecsPreviousFrame) / 1000.0;
	_millisecsPreviousFrame = SDL_GetTicks();
}

void Game::Render()
{
	SDL_SetRenderDrawColor(_renderer,21, 21, 21, 255);
	SDL_RenderClear(_renderer);
	// ToDo: Render all game objects
	SDL_RenderPresent(_renderer);
}

void Game::Destroy()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}
