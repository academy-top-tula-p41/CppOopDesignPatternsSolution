#pragma once
#include <iostream>

class ICommand
{
public:
	virtual ~ICommand() = default;
	virtual void Execute() = 0;
	virtual bool CanExecute() { return true; }
};

class SimpleCommand : public ICommand
{
	std::string message;
public:
	SimpleCommand(std::string message = "")
		: message{ message }{}

	void Execute() override
	{
		std::cout << "Print message: " << message << "\n";
	}
};

class Receiver
{
public:
	void DoSomething(std::string message)
	{
		std::cout << "Receiver message: " << message << "\n";
	}
};

class ComplexCommand : public ICommand
{
	Receiver* receiver;

	std::string message;
public:
	ComplexCommand(Receiver* receiver,
				   std::string message)
		: receiver{ receiver },
		message{ message }{ }

	void Execute() override
	{
		std::cout << "Complex Command:\n";
		receiver->DoSomething(message);
	}
};

class Invoker
{
	ICommand* command;
public:
	Invoker(ICommand* command) : command{ command } {}

	void Invoke()
	{
		std::cout << "Command Invoke\n";
		if (command->CanExecute())
			command->Execute();
	}

	void SetCommand(ICommand* command)
	{
		this->command = command;
	}
};

class CommandClient
{
public:
	void ClientCode()
	{
		SimpleCommand* simpleCommand = new SimpleCommand("Simple command");
		simpleCommand->Execute();
		std::cout << "\n";

		Invoker* invoker = new Invoker(simpleCommand);
		invoker->Invoke();
		std::cout << "\n";

		ComplexCommand* complexCommand = new ComplexCommand(new Receiver(), "Complex Command");
		complexCommand->Execute();
		std::cout << "\n";

		invoker->SetCommand(complexCommand);
		invoker->Invoke();
		std::cout << "\n";

		simpleCommand->Execute();
		std::cout << "\n";
	}
};