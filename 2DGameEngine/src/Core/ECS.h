#pragma once
#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>
#include "IPool.h"
#include "Pool.h"
#include <unordered_map>
#include <typeindex>
#include <set>

const unsigned int MAX_COMPONENTS{ 32 };
typedef std::bitset<MAX_COMPONENTS> Signature;

class Entity
{
private:
	int _id{};

public:
	Entity(int id) : _id(id) {};
	Entity(const Entity& entity) = default;
	int GetId() const { return _id; }
	Entity& operator = (const Entity& other) = default;
	bool operator == (const Entity& other) const { return _id == other._id; }
	bool operator != (const Entity& other) const { return _id != other._id; }
	bool operator > (const Entity& other) const { return _id > other._id; }
	bool operator < (const Entity& other) const { return _id < other._id; }
};

struct IComponent
{
protected:
	static int NextId;
};

template<typename TComponent>
class Component : public IComponent
{
public:
	static int GetId()
	{
		static auto id = NextId++;
		return id;
	}
};

#pragma region System
/// <summary>
/// Processes entities that contain a specific signature
/// </summary>
class System
{
private:
	Signature _componentSignature{};
	std::vector<Entity> _entities{};

public:
	System() = default;
	~System() = default;
	void AddEntity(Entity entity);
	void RemoveEntity(Entity entity);
	std::vector<Entity> GetEntities() const;
	const Signature& GetComponentSignature();
	template<typename T> void RequireComponent();
};

template<typename TComponent>
inline void System::RequireComponent()
{
	const auto componentId = Component<TComponent>::GetId();
	_componentSignature.set(componentId);
}
#pragma endregion

#pragma region Registry
/// <summary>
/// Manages the creation and destruction of entities, systems and components 
/// </summary>
class Registry
{
private:
	int _entities{ 0 };
	std::vector<IPool*> _componentPools{};
	std::vector<Signature> _entityComponentSignatures{};
	std::unordered_map<std::type_index, System*> _systems;
	std::set<Entity> _entitiesToBeAdded{};
	std::set<Entity> _entitiesToBeDestroyed{};

public:
	Registry() = default;
	Entity CreateEntity();
	void AddEntityToSystem(Entity entity);
	template<typename TComponent, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
	template<typename TComponent> void RemoveComponent(Entity entity);
	template<typename TComponent> bool HasComponent(Entity entity) const;
	template<typename TComponent> TComponent& GetComponent(Entity entity) const;
	void Update();
};

template<typename TComponent, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs&& ...args)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetId();
	if (componentId >= _componentPools.size())
	{
		_componentPools.resize(componentId + 1, nullptr);
	}
	if (!_componentPools[componentId])
	{
		auto newComponentPool = new Pool<TComponent>();
		_componentPools[componentId] = newComponentPool;
	}
	auto componentPool = Pool<TComponent>(_componentPools[componentId]);
	if (entityId >= componentPool->GetSize())
	{
		componentPool->Resize(_entities);
	}
	TComponent newComponent(std::forward<TArgs>(args)...);
	componentPool->Set(entityId, newComponent);
	_entityComponentSignatures[entityId].set(componentId);
}

template<typename TComponent> 
void Registry::RemoveComponent(Entity entity)
{
	const auto componentId = Component<TComponent>::GetId();
	_entityComponentSignatures[entity.GetId()].set(componentId, false);
}

template<typename TComponent>
bool Registry::HasComponent(Entity entity) const
{
	const auto componentId = Component<TComponent>::GetId();
	return _entityComponentSignatures[entity.GetId()].test(componentId);
}

#pragma endregion

#endif