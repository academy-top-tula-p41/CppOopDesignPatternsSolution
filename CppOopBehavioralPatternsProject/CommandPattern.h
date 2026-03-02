#pragma once
#include <iostream>
#include <stack>

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

///

// Receiver
class Television
{
	bool isPower;
	int soundVolume;

	const int maxSoundVolume{ 5 };
public:
	Television() : isPower{ false }, soundVolume{}{}

	void PowerOn()
	{
		std::cout << "Television power ON\n";
		isPower = true;
	}

	void PowerOff()
	{
		std::cout << "Television power OFF\n";
		isPower = false;
	}

	void VolumeInc()
	{
		if (soundVolume < maxSoundVolume)
			std::cout << "Television. Sound increment. Volume: " << ++soundVolume << "\n";
	}

	void VolumeDec()
	{
		if (soundVolume > 0)
			std::cout << "Television. Sound decrement. Volume: " << --soundVolume << "\n";
	}

	bool IsPower() const { return this->isPower; }
	void Info()
	{
		std::cout << "Power: " << ((isPower) ? "ON" : "OFF")
			<< ", Sound: " << soundVolume << "\n";
	}
};


// Commands
class IUndoCommand : public ICommand
{
public:
	virtual void Undo() = 0;
};

class ITvCommand : public IUndoCommand
{
protected:
	Television* tv{ nullptr };
public:
	ITvCommand(Television* tv) : tv{ tv } {}
};

class PowerOnTvCommand : public ITvCommand
{
public:
	PowerOnTvCommand(Television* tv) 
		: ITvCommand(tv){ }
	void Execute() override { tv->PowerOn(); }
	bool CanExecute() override { return !tv->IsPower(); }
	void Undo() override { tv->PowerOff(); }
};

class PowerOffTvCommand : public ITvCommand
{
public:
	PowerOffTvCommand(Television* tv)
		: ITvCommand(tv) { }
	void Execute() override { tv->PowerOff(); }
	bool CanExecute() override { return tv->IsPower(); }
	void Undo() override { tv->PowerOn(); }
};

class SoundUpTvCommand : public ITvCommand
{
public:
	SoundUpTvCommand(Television* tv)
		: ITvCommand(tv) {}
	void Execute() override { tv->VolumeInc(); }
	bool CanExecute() override { return tv->IsPower(); }
	void Undo() override { tv->VolumeDec(); }
};

class SoundDownTvCommand : public ITvCommand
{
public:
	SoundDownTvCommand(Television* tv)
		: ITvCommand(tv) {}
	void Execute() override { tv->VolumeDec(); }
	bool CanExecute() override { return tv->IsPower(); }
	void Undo() override { tv->VolumeInc(); }
};

// Invoker
class Controller
{
	ITvCommand* powerOn;
	ITvCommand* powerOff;
	ITvCommand* soundUp;
	ITvCommand* soundDown;
public:
	Controller(ITvCommand* powerOn,
				ITvCommand* powerOff,
				ITvCommand* soundUp,
				ITvCommand* soundDown)
		: powerOn{ powerOn },
		powerOff{ powerOff },
		soundUp{ soundUp },
		soundDown{ soundDown }{ }

	void ButtonPower()
	{
		if (powerOn->CanExecute())
			powerOn->Execute();
		else if (powerOff->CanExecute())
			powerOff->Execute();
	}

	void ButtonSoundPlus()
	{
		if (soundUp->CanExecute())
			soundUp->Execute();
	}

	void ButtonSoundMinus()
	{
		if (soundDown->CanExecute())
			soundDown->Execute();
	}
};

class ControllerMobileApp
{
	ITvCommand* powerOn;
	ITvCommand* powerOff;
	ITvCommand* soundUp;
	ITvCommand* soundDown;

	std::stack<IUndoCommand*> history;
public:
	ControllerMobileApp(ITvCommand* powerOn,
		ITvCommand* powerOff,
		ITvCommand* soundUp,
		ITvCommand* soundDown)
		: powerOn{ powerOn },
		powerOff{ powerOff },
		soundUp{ soundUp },
		soundDown{ soundDown } {
	}

	void PowerOnMenuItem()
	{
		if (powerOn->CanExecute())
		{
			powerOn->Execute();
			history.push(powerOn);
		}
	}

	void PowerOffMenuItem()
	{
		if (powerOff->CanExecute())
		{
			powerOff->Execute();
			history.push(powerOff);
		}
	}

	void SoundPlusMenuItem()
	{
		if (soundUp->CanExecute())
		{
			soundUp->Execute();
			history.push(soundUp);
		}
	}

	void SoundMinusMenuItem()
	{
		if (soundDown->CanExecute())
		{
			soundDown->Execute();
			history.push(soundDown);
		}
	}

	void UndoMenuItem()
	{
		if (!history.empty())
		{
			history.top()->Undo();
			history.pop();
		}
	}
};