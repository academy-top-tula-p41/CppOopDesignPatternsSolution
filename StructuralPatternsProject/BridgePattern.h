#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <ctime>

namespace BridgeNamespace
{
	class Implementation
	{
	public:
		virtual ~Implementation() = default;
		virtual std::string ImplementationOperation() = 0;
	};

	class Abstraction
	{
	protected:
		Implementation* implementation;
	public:
		Abstraction(Implementation* implementation)
			: implementation{ implementation }{ }
		virtual ~Abstraction() = default;

		virtual std::string AbstractOperation()
		{
			return "Abstraction. Base operation with "
				+ this->implementation->ImplementationOperation();
		}
	};

	class ConcreteImplementationA : public Implementation
	{
	public:
		std::string ImplementationOperation() override
		{
			return "Implementation A";
		}
	};

	class ConcreteImplementationB : public Implementation
	{
	public:
		std::string ImplementationOperation() override
		{
			return "Implementation B";
		}
	};

	class BridgeClient
	{
	public:
		void ClentCode(Abstraction* abstraction)
		{
			std::cout << abstraction->AbstractOperation() << "\n";
		}
	};

	class ExtendedAbstraction : public Abstraction
	{

	};


	//
	class LoggerType
	{
	public:
		virtual void MessageSend(std::string message) = 0;
	};

	class Logger
	{
	protected:
		LoggerType* loggerType;

		std::string CreateMessage(std::string message)
		{
			auto now = std::chrono::system_clock::now();
			auto now_time = std::chrono::system_clock::to_time_t(now);
			return std::ctime(&now_time) + std::string(": ") + message;
		}
	};

}
