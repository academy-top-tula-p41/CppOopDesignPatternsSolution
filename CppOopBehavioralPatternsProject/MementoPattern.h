#pragma once
#include <iostream>
#include <vector>
#include <string>

class Memento
{
public:
	virtual ~Memento() = default;

	virtual std::string GetName() const = 0;
	virtual std::string GetDate() const = 0;
	virtual std::string GetState() const = 0;
};

class ConcreteMemento : public Memento
{
	std::string date;
	std::string state;
public:
	ConcreteMemento(std::string state)
		: state{ state }
	{
		std::time_t now = std::time(nullptr);
		char* now_c = new char[26];
		ctime_s(now_c, 26, &now);
		this->date = std::string(now_c);
	}

	std::string GetName() const override
	{
		return this->date + " ("
			+ this->state.substr(0, 10)
			+ "...)";
	}
	std::string GetDate() const override
	{
		return this->date;
	}
	std::string GetState() const override
	{
		return this->state;
	}
};

class Originator
{
	std::string state;

	std::string GenerateRandomState(int length = 30)
	{
		const char alphaDigits[] =
			"0123456789"
			"abcdefghijklmnopqrstuvwxyz"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

		int alphaDigitsLength = sizeof(alphaDigits) - 1;

		std::string randomState{ "" };
		for (int i{}; i < alphaDigitsLength; i++)
			randomState += alphaDigits[std::rand() % alphaDigitsLength];

		return randomState;
	}

public:
	Originator(std::string initState) : state{ initState }
	{
		std::cout << "Orginator. Base state: " << this->state << "\n";
	}

	void DoSomething()
	{
		this->state = this->GenerateRandomState();
		std::cout << "Orginator. New state: " << this->state << "\n";
	}

	Memento* CreateMeneto()
	{
		return new ConcreteMemento(this->state);
	}

	void RestoreState(Memento* memento)
	{
		this->state = memento->GetState();
		std::cout << "Orginator. Restore state: " << this->state << "\n";
		delete memento;
	}
};

class Caretaker
{
	Originator* originator;
	std::vector<Memento*> history;
public:
	Caretaker(Originator* originator) : originator{ originator }{}
	~Caretaker()
	{
		for (auto memento : history)
			delete memento;
		history.clear();
	}

	void Backup()
	{
		std::cout << "Caretaker. Make backup\n";
		this->history.push_back(originator->CreateMeneto());
	}

	void Undo()
	{
		if (history.empty()) return;

		auto memento = this->history.back();
		this->history.pop_back();

		std::cout << "Caretaker. Undo state: " << memento->GetName() << "\n";
		this->originator->RestoreState(memento);
	}

	void History()
	{
		std::cout << "\n---------- Caretaker History ---------\n";

		for (auto memento : history)
			std::cout << memento->GetName() << "\n";

		std::cout << "\n--------------------------------------\n";
	}
};

class MementoClient
{
public:
	void ClientCode()
	{
		Originator* originator = new Originator("First state for Originator");

		Caretaker* caretaker = new Caretaker(originator);
		caretaker->Backup();

		originator->DoSomething();
		caretaker->Backup();

		originator->DoSomething();
		originator->DoSomething();
		caretaker->Backup();

		originator->DoSomething();
		caretaker->Backup();

		caretaker->History();

		caretaker->Undo();
		caretaker->Undo();
		caretaker->Undo();
		caretaker->Undo();
		caretaker->Undo();
		caretaker->Undo();
	}
};

///
// Service
class Game
{
public:
	int Play()
	{
		return 2 + rand() % 6;
	}
};

class Player;

// Memento
class PlayerState
{
	int points;
	int level;

	Player* player;
public:
	PlayerState(Player* player, int level, int points)
		: player{ player }, level{ level }, points{ points }{ }

	int Points() const { return this->points; }
	int Level() const { return this->level; }
};

// Originator
class IOriginator
{
public:
	 
};

class Player
{
	int points;
	int level;

	Game* game;
public:
	Player() : points{}, level{ 1 }, game{ new Game() }{}

	void PlayRound()
	{
		this->points += game->Play();
		this->level += this->points / 10;
		this->points = this->points % 10;
	}

	std::string State() const
	{
		return "Player. Level: " + std::to_string(this->level)
			+ ", Points: " + std::to_string(this->points);
	}

	PlayerState* Save()
	{
		return new PlayerState(this, this->level, this->points);
	}

	void Load(PlayerState* state)
	{
		this->level = state->Level();
		this->points = state->Points();

		delete state;
	}
};

class PlayerHistory
{
	std::vector<PlayerState*> history;
public:
	void Push(PlayerState* state)
	{
		history.push_back(state);
	}

	PlayerState* Pop()
	{
		auto state = history.back();
		history.pop_back();
		return state;
	}

	void History()
	{
		std::cout << "\n---------- Caretaker History ---------\n";

		for (auto state : history)
			std::cout << "Level: " << state->Level() 
					<< ", Points: " << state->Points() << "\n";

		std::cout << "\n--------------------------------------\n";
	}
};