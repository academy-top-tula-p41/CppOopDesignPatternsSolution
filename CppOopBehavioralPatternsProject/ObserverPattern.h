#pragma once
#include <iostream>
#include <list>

// Observer - Subscriber
class Observer
{
	std::string name;
public:
	Observer(std::string name)
		: name{ name }{ }

	virtual ~Observer() = default;
	virtual void EventHandler(std::string stateObservable) = 0;
	std::string Name() const { return this->name; }
};

// Observable - Publisher
class Observable
{
public:
	virtual ~Observable() = default;
	virtual void AddObserver(Observer* observer) = 0;
	virtual void RemoveObserver(Observer* observer) = 0;
	virtual void NotifyObservers() = 0;
};

class ConcreteObservable : public Observable
{
	std::list<Observer*> observers;
	std::string state;

	std::string GenerateState(int length = 20)
	{
		std::string alpha = "abcdefghijklmnopqrstuvwxyz"
							"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		std::string randomState = "";
		for (int i{}; i < length; i++)
			randomState += alpha[std::rand() % alpha.length()];
		return randomState;
	}
public:
	void AddObserver(Observer* observer) override
	{
		std::cout << "Observable. Add new observer "
			<< observer->Name() << "\n";
		observers.push_back(observer);
	}

	void RemoveObserver(Observer* observer) override
	{
		std::cout << "Observable. Remove observer "
			<< observer->Name() << "\n";
		observers.remove(observer);
	}

	void NotifyObservers() override
	{
		std::cout << "Observable. Notify my observers\n";
		for (auto observer : observers)
			observer->EventHandler(this->state);
	}

	void BuisnessLogic()
	{
		this->state = this->GenerateState();
		std::cout << "\nObservable. Change state: "
			<< this->state << "\n";
		this->NotifyObservers();
	}
};

class ConcreteObserver : public Observer
{
	std::string state;
	Observable* observable{};
public:
	ConcreteObserver(std::string name, Observable* observable = nullptr)
		: Observer(name), observable{ observable }
	{
		if (this->observable)
			this->Attach(this->observable);
	}

	void EventHandler(std::string stateObservable) override
	{
		std::cout << "Observer " << this->Name()
			<< ". Handled event from Observable\n";
		this->state = stateObservable;
		std::cout << "\tNew state: " << this->state << "\n";
	}

	void Attach(Observable* observable)
	{
		std::cout << "Observer " << this->Name()
			<< ". Attach to Observable\n";
		this->observable = observable;
		this->observable->AddObserver(this);
	}

	void Detach()
	{
		std::cout << "Observer " << this->Name()
			<< ". Detach from Observable\n";
		this->observable->RemoveObserver(this);
	}
};

class ObserverClient
{
public:
	void ClientCode()
	{
		ConcreteObservable* publisher = new ConcreteObservable();

		ConcreteObserver* subsriber = new ConcreteObserver("Subscriber A");
		subsriber->Attach(publisher);

		ConcreteObserver* observer = new ConcreteObserver("Observer B", publisher);

		for (int i{}; i < 3; i++)
			publisher->BuisnessLogic();
		
		subsriber->Detach();

		publisher->BuisnessLogic();
	}
};