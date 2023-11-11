#pragma once
#ifndef POOL_H
#define POOL_H

#include "IPool.h"
#include <vector>

template <typename T>
class Pool : public IPool
{
private:
	std::vector<T> _data;

public:
	Pool(int size = 100) { _data.resize(size); }
	virtual ~Pool() = default;
	bool IsEmpty() const { return _data.empty(); }
	int GetSize() const { return _data.size(); }
	void Resize(int size) { _data.resize(size); }
	void Clear() { _data.clear(); }
	void Add(T object) { _data.push_back(object); }
	void Set(int index, T object) { _data[index] = object; }
	T& Get(int index) { return static_cast<T&>(_data[index]); }
	T& operator [](unsigned int index) { return _data[index]; }
};

#endif