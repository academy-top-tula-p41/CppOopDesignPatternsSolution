#pragma once
#include <mutex>

class Singleton
{
	static Singleton* instance;
	Singleton(){}
public:
	static Singleton* GetInstance()
	{
		if (!instance)
			instance = new Singleton();
		return instance;
	}
};

Singleton* Singleton::instance = nullptr;


std::mutex m;

class OperationSystem
{
	static OperationSystem* system;
	std::string title;

	OperationSystem(std::string title)
		: title{ title }{ }

public:
	std::string Title() { return title; }

	static OperationSystem* GetSystem(std::string title)
	{
		std::lock_guard<std::mutex> lock(m);

		if (!system)
			system = new OperationSystem(title);
		return system;
	}
};

OperationSystem* OperationSystem::system = nullptr;

class Computer
{
	OperationSystem* os;
public:
	void Lounch(std::string osName)
	{
		os = OperationSystem::GetSystem(osName);
	}

	OperationSystem*& System() { return os; }
};
