#include "Game.h"
#include <SDL.h>
#include <iostream>

Game::Game() : 
	_isRunning{ false },
	WindowWidth{ 800 },
	WindowHeight{ 600 }
{

}

Game::~Game()
{

}

void Game::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error initializing SDL." << std::endl;
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
		std::cerr << "Error creating SDL window." << std::endl;
		return;
	}
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!_renderer)
	{
		std::cerr << "Error creating SDL renderer." << std::endl;
		return;
	}
	SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
	_isRunning = true;
}

void Game::Run()
{
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
	// ToDo: Update game objects
}

void Game::Render()
{
	SDL_SetRenderDrawColor(_renderer,0, 0, 0, 255);
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
