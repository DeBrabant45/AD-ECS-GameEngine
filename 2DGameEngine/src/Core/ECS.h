#pragma once
#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENTS{ 32 };
typedef std::bitset<MAX_COMPONENTS> Signature;

class Entity
{
private:
	int _id{};

public:
	Entity(int id) : _id(id) {};
	Entity(const Entity& entity) = default;
	int GetID() const { return _id; }
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

class Registry
{

};

#endif