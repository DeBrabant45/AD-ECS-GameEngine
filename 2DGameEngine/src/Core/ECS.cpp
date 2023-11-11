#include "ECS.h"
#include <algorithm>
#include "../Loggers/Logger.h"

int IComponent::NextId{ 0 };

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

Entity Registry::CreateEntity()
{
	auto entityId = _entities++;
	if (entityId >= _entityComponentSignatures.size())
		_entityComponentSignatures.resize(entityId + 1);

	Entity newEntity(entityId);
	_entitiesToBeAdded.insert(newEntity);
	Logger::Log("Entity created with id = " + std::to_string(entityId));
	return newEntity;
}

void Registry::AddEntityToSystem(Entity entity)
{

}

void Registry::Update()
{

}