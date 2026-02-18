#pragma once
#include <iostream>
#include <map>

namespace FlyweightNamespace
{
	class SharedState
	{
		std::string name;
		std::string blob;
	public:
		SharedState(std::string name, std::string blob)
			: name{ name }, blob{ blob }{}

		std::string Name() { return name; }
		std::string Blob() { return blob; }

		std::string ToString()
		{
			return "Name: " + name + ", Blob: " + blob;
		}
	};

	class UniqueState
	{
		std::string owner;
	public:
		UniqueState(std::string owner) : owner{ owner } {}

		std::string ToString() { return "Owner: " + owner; }
	};


	class Flyweight
	{
		SharedState* sharedState;
	public:
		Flyweight(SharedState* sharedState)
			: sharedState{ new SharedState(*sharedState) }{}
		Flyweight(const Flyweight& other)
			: sharedState{ new SharedState(*other.sharedState) } {}
		~Flyweight() { delete sharedState; }

		SharedState* GetSharedState() const { return sharedState; }

		void Operation(UniqueState& uniqueState) const
		{
			std::cout << "Flyweight: Shared State: " << sharedState->ToString()
				<< ", Unique State: " << uniqueState.ToString() << "\n";
		}
	};

	class FlyweightFactory
	{
		std::map<std::string, Flyweight> flyweights;

		std::string Key(SharedState& sharedState)
		{
			return sharedState.Name() + "_" + sharedState.Blob();
		}

	public:
		FlyweightFactory(std::initializer_list<SharedState> sharedStates)
		{
			for (auto state : sharedStates)
				this->flyweights.insert(std::make_pair(this->Key(state), Flyweight(&state)));
		}

		Flyweight GetFlyweight(SharedState& sharedStates)
		{
			std::string key = Key(sharedStates);
			if (!this->flyweights.contains(key))
				flyweights.insert(std::make_pair(key, Flyweight(&sharedStates)));

			return flyweights.at(key);
		}

		void ListFlyweights()
		{
			for (auto fly : flyweights)
				std::cout << fly.second.GetSharedState()->ToString() << "\n";
		}
	};
}