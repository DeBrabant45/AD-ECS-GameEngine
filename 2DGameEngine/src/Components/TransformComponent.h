#pragma once
#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>
#include "../Core/ECS.h"

struct TransformComponent : Component
{
	glm::vec2 Position{};
	glm::vec2 Scale{};
	double Rotation{};
};

#endif 