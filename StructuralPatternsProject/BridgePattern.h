#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>

//#include <ctime>

using namespace std::chrono_literals;

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
		virtual ~LoggerType() = default;
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
	public:
		Logger(LoggerType* loggerType)
			: loggerType{ loggerType }{ }

		virtual void Log(std::string message) = 0;
	};

	class SimpleThreadLogger : public Logger
	{
	public:
		SimpleThreadLogger(LoggerType* loggerType)
			: Logger(loggerType){ }

		void Log(std::string message) override
		{
			loggerType->MessageSend(this->CreateMessage(message));
		}
	};

	class ParallelThreadLogger : public Logger
	{
	public:
		ParallelThreadLogger(LoggerType* loggerType)
			: Logger(loggerType){ }

		void ThreadLog(std::string message)
		{
			this->loggerType->MessageSend(message);
		}

		void Log(std::string message) override
		{
			std::jthread th(ThreadLog, message);
		}
	};

	class ConsoleLoggerType : public LoggerType
	{
	public:
		void MessageSend(std::string message) override
		{
			std::cout << message << "\n";
		}
	};

	class FileLoggerType : public LoggerType
	{
		std::string fileName;
		std::ofstream fileOut;
	public:
		FileLoggerType(std::string fileName)
			: fileName{ fileName }
		{
			fileOut.open(this->fileName, std::ios::app);
		}

		~FileLoggerType()
		{
			fileOut.close();
		}

		void MessageSend(std::string message) override
		{
			fileOut << message << "\n";
		}
	};


	class System
	{
		Logger* logger;
	public:
		System(Logger* logger) 
			: logger{ logger }{}

		void Work()
		{
			for (int i{}; i < 5; i++)
			{
				int ms = 1000 + rand() % 4001;
				std::chrono::duration<int, std::milli> d(ms);
				std::this_thread::sleep_for(d);

				logger->Log(std::to_string(i + 1) + " message");
			}
		}
	};
}
