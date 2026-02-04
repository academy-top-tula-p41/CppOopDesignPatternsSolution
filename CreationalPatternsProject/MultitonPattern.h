#pragma once
#include <iostream>
#include <map>
#include <mutex>

std::mutex m;

enum class SingletonType
{
	Zero,
	One,
	Two
};

class Multiton
{
	static std::map<SingletonType, Multiton*> instances;
	int type;
	Multiton(int type) : type{ type }{}
public:
	static Multiton* GetInstance(SingletonType type)
	{
		std::lock_guard<std::mutex> lock(m);

		if (!instances.contains(type))
			instances.insert(std::make_pair(type, new Multiton((int)type)));

		return instances.at(type);
	}
};

std::map<SingletonType, Multiton*> Multiton::instances;