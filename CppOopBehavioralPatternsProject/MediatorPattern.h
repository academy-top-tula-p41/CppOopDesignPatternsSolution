#pragma once
#include <iostream>

class Component;

class Mediator
{
public:
	virtual void Notify(Component* sender, std::string event) = 0;
};

class Component
{
protected:
	Mediator* mediator;
public:
	Component(Mediator* mediator = nullptr) : mediator{ mediator }{}
	
	void SetMediator(Mediator* mediator) { this->mediator = mediator; }
};

class ComponentA : public Component
{
public:
	void DoOne()
	{
		std::cout << "Component A does ONE\n";
		mediator->Notify(this, "ONE");
	}

	void DoTwo()
	{
		std::cout << "Component A does TWO\n";
		mediator->Notify(this, "TWO");
	}
};

class ComponentB : public Component
{
public:
	void DoThree()
	{
		std::cout << "Component B does THREE\n";
		mediator->Notify(this, "THREE");
	}

	void DoFore()
	{
		std::cout << "Component B does FORE\n";
		mediator->Notify(this, "FORE");
	}
};

class ConcreteMediator : public Mediator
{
	ComponentA* componentA;
	ComponentB* componentB;
public:
	ConcreteMediator(ComponentA* componentA, ComponentB* componentB)
		: componentA{ componentA }, componentB{ componentB }
	{ 
		componentA->SetMediator(this);
		componentB->SetMediator(this);
	}

	void Notify(Component* sender, std::string event) override
	{
		if (event == "ONE")
		{
			std::cout << "Mediator react on A:\n";
			componentB->DoThree();
		}

		if (event == "FORE")
		{
			std::cout << "Mediator react on B:\n";
			componentA->DoTwo();
			componentB->DoThree();
		}
	}
};

class MediatorClient
{
public:
	void ClientCode()
	{
		ComponentA* componentA = new ComponentA();
		ComponentB* componentB = new ComponentB();

		ConcreteMediator* mediator = new ConcreteMediator(componentA, componentB);
		componentA->DoOne();
		std::cout << "\n";
		componentB->DoFore();

		delete componentA;
		delete componentB;
		delete mediator;
	}
};

//

enum class CollegueType
{
	Customer,
	Designer,
	Developer,
	Tester
};

enum class EventType
{
	Order,
	Modeling,
	Project,
	Development,
	TestingWrong,
	Debugging,
	TestingGood,
	Release,
	Payment
};

class Collegue;

class Manager
{
public:
	virtual void ReadReport(Collegue* collegue, std::string report, EventType event) = 0;
};

class Collegue
{
	Manager* manager;
	CollegueType type;
public:
	Collegue(CollegueType type, Manager* manager = nullptr)
		: manager{ manager }, type{ type }{ }

	void SetManager(Manager* manager) { this->manager = manager; }
	CollegueType Type() const { return this->type; }

	virtual void SendReport(std::string report, EventType event)
	{
		manager->ReadReport(this, report, event);
	}
};

class CustomerCollegue : public Collegue
{
public:
	CustomerCollegue(Manager* manager)
		: Collegue(CollegueType::Customer, manager){ }
	
	void PlaceAnOrder()
	{
		SendReport("I need an app", EventType::Order);
	}

	void Payment()
	{
		SendReport("Thanks. I Pay", EventType::Payment);
	}
};

class DesignerCollegue : public Collegue
{
public:
	DesignerCollegue(Manager* manager)
		: Collegue(CollegueType::Designer, manager) {}

	void MakeModel()
	{
		SendReport("I created Model", EventType::Modeling);
	}

	void CreateProject()
	{
		SendReport("I created Project", EventType::Project);
	}
};

class DeveloperCollegue : public Collegue
{
public:
	DeveloperCollegue(Manager* manager)
		: Collegue(CollegueType::Developer, manager) {}

	void Developing()
	{
		SendReport("I developing code of project", EventType::Development);
	}

	void Debugging()
	{
		SendReport("I Debugged code of project", EventType::Debugging);
	}
};

class TesterCollegue : public Collegue
{
public:
	TesterCollegue(Manager* manager)
		: Collegue(CollegueType::Tester, manager) {}

	void TestingOnBags()
	{
		SendReport("I found bugs in code", EventType::TestingWrong);
	}

	void TestingFinal()
	{
		SendReport("I not found errors!", EventType::TestingGood);
	}
};

class ProjectManager : public Manager
{
public:
};