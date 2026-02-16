#pragma once
#include <iostream>

namespace FacadeNamespace
{
	class SubsystemA
	{
	public:
		std::string Operation1()
		{
			return "Subsystem A. Ready!";
		}

		// ...

		std::string OperationN()
		{
			return "Subsystem A. Go!";
		}
	};

	class SubsystemB
	{
	public:
		std::string Operation1()
		{
			return "Subsystem B. Ready!";
		}

		// ...

		std::string OperationM()
		{
			return "Subsystem A. Fire!";
		}
	};

	class Facade
	{
		SubsystemA* subsystemA;
		SubsystemB* subsystemB;
	public:
		Facade(SubsystemA* subsystemA = nullptr,
			SubsystemB* subsystemB = nullptr)
		{
			this->subsystemA = subsystemA ? subsystemA : new SubsystemA();
			this->subsystemB = subsystemB ? subsystemB : new SubsystemB();
		}
		~Facade()
		{
			delete subsystemA;
			delete subsystemB;
		}
			
		std::string Operation()
		{
			std::string result = "Facade init subsystems:\n";
			result += "\t" + subsystemA->Operation1() + "\n";
			result += "\t" + subsystemB->Operation1() + "\n";

			result += "Facade activate subsystems:\n";
			result += "\t" + subsystemA->OperationN() + "\n";
			result += "\t" + subsystemB->OperationM() + "\n";

			return result;
		}

	};

	class FacadeClient
	{
	public:
		void ClientCode(Facade* facade)
		{
			std::cout << facade->Operation() << "\n";
		}
	};
}
