#pragma once
#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../Core/ECS.h"

class MovementSystem : public System
{
public:
	MovementSystem();
	void Update();
};

#endif