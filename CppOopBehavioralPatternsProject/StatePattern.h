#pragma once
#include <iostream>

class Context;

class State
{
protected:
	Context* context{};
public:
	virtual ~State() = default;
	void SetContext(Context* context) { this->context = context; }

	virtual void ExecuteOne() = 0;
	virtual void ExecuteTwo() = 0;
};

class Context
{
	State* state{};
public:
	Context(State* initState)
		: state{ initState }
	{ 
		this->state->SetContext(this);
		std::cout << "Context. Init state " << typeid(*state).name() << "\n";
	}

	void TransitionTo(State* state)
	{
		std::cout << "Context. Transition to " << typeid(*state).name() << "\n";
		
		// Optional
		if (this->state)
			delete this->state;

		this->state = state;
		this->state->SetContext(this);
	}

	void HandlerOne() { this->state->ExecuteOne(); }
	void HandlerTwo() { this->state->ExecuteTwo(); }
};

class ConcreteStateA : public State
{
public:
	void ExecuteOne() override;
	void ExecuteTwo() override
	{
		std::cout << "State A. Execute Two\n";
	}
};

class ConcreteStateB : public State
{
public:
	void ExecuteOne() override
	{
		std::cout << "State B. Execute One\n";
	}
	void ExecuteTwo() override
	{
		std::cout << "State B. Execute Two\n";
		std::cout << "State B. Change Context\n";
		this->context->TransitionTo(new ConcreteStateA());
	}
};

void ConcreteStateA::ExecuteOne()
{
	std::cout << "State A. Execute One\n";
	std::cout << "State A. Change Context\n";
	this->context->TransitionTo(new ConcreteStateB());
}


class StateClient
{
public:
	void ClientCode()
	{
		Context* context = new Context(new ConcreteStateA());
		context->HandlerOne();
		context->HandlerTwo();
		std::cout << "\n";
		
		context->TransitionTo(new ConcreteStateB());
		context->HandlerOne();
		context->HandlerTwo();
		std::cout << "\n";
	}
};

///

class Water;

class WaterState
{
protected:
	Water* water{};
public:
	void SetWater(Water* water) { this->water = water; }

	virtual void Heat() = 0;
	virtual void Frost() = 0;
};

class Water
{
	WaterState* state{};
public:
	Water(WaterState* state) : state { state }{}

	void Heating() { this->state->Heat(); }

	void Frosting() { this->state->Frost(); }

	WaterState*& State()
	{
		if (this->state) delete this->state;
		return this->state;
	}
};

class GasState : public WaterState
{
public:
	void Heat() override;
	void Frost() override;
};

class LiquidState : public WaterState
{
public:
	void Heat() override;
	void Frost() override;
};

class SolidState : public WaterState
{
public:
	void Heat() override;
	void Frost() override;
};

void GasState::Heat()
{  
	std::cout << "Gas to hot Gas\n";
}

inline void GasState::Frost()
{
	std::cout << "Gas to Liquid\n";

	auto newState = new LiquidState();
	newState->SetWater(this->water);

	this->water->State() = newState;
}

void LiquidState::Heat()
{
	std::cout << "Liquid to Gas\n";

	auto newState = new GasState();
	newState->SetWater(this->water);

	this->water->State() = newState;
}

inline void LiquidState::Frost()
{
	std::cout << "Liquid to Ice\n";

	auto newState = new SolidState();
	newState->SetWater(this->water);

	this->water->State() = newState;
}

void SolidState::Heat()
{
	std::cout << "Ice to Liquid\n";

	auto newState = new LiquidState();
	newState->SetWater(this->water);

	this->water->State() = newState;
}

inline void SolidState::Frost()
{
	std::cout << "Ice to hard Ice\n";
}

class WaterClient
{
public:
	void Experiment()
	{
		WaterState* state = new LiquidState();
		Water* water = new Water(state);
		state->SetWater(water);

		for (int i{}; i < 5; i++)
			water->Heating();

		for (int i{}; i < 5; i++)
			water->Frosting();
	}
};
