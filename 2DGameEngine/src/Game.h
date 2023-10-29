#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL.h>

class Game
{
private:
	bool _isRunning{};
	SDL_Window* _window{};
	SDL_Renderer* _renderer{};

public:
	int WindowWidth{};
	int WindowHeight{};

public:
	Game();
	~Game();
	void Initialize();
	void Run();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();
};

#endif 