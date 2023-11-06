#include "ECS.h"
#include <algorithm>

void System::AddEntity(Entity entity)
{
	_entities.push_back(entity);
}

void System::RemoveEntity(Entity entity)
{
	_entities.erase(std::remove_if(
		_entities.begin(),
		_entities.end(),
		[&entity](Entity other)
		{
			return entity == other;
		}),
		_entities.end());
}

std::vector<Entity> System::GetEntities() const
{
	return _entities;
}

const Signature& System::GetComponentSignature()
{
	return _componentSignature;
}
