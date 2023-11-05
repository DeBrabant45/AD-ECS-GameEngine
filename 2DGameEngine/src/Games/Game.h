#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL.h>

const int FPS{ 60 };
const int MILLISECS_PER_FRAME{ 1000 / FPS };

class Game
{
private:
	bool _isRunning{};
	Uint32 _millisecsPreviousFrame{ 0 };
	SDL_Window* _window{};
	SDL_Renderer* _renderer{};

public:
	int WindowWidth{};
	int WindowHeight{};

public:
	Game();
	~Game();
	void Initialize();
	void Setup();
	void Run();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();
};

#endif 