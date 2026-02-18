#pragma once
#include <iostream>
#include <vector>
#include <map>

namespace ChainNamespace
{
	class IHandler
	{
	public:
		virtual IHandler* SetNext(IHandler* handler) = 0;
		virtual std::string Handle(std::string request) = 0;
	};

	class BaseHandler : public IHandler
	{
	protected:
		IHandler* nextHandler;

	public:
		BaseHandler(IHandler* nextHandler = nullptr)
			: nextHandler{ nextHandler }{ }

		IHandler* SetNext(IHandler* handler) override
		{
			this->nextHandler = handler;
			return handler;
		}

		std::string Handle(std::string request) override
		{
			if (this->nextHandler)
				return this->nextHandler->Handle(request);

			return "";
		}
	};

	class ConcreteHandlerA : public BaseHandler
	{
	public:
		std::string Handle(std::string request)
		{
			if (request == "RequestA")
				return "Handler A, handlerered request " + request + "\n";
			else
				return BaseHandler::Handle(request);
		}
	};

	class ConcreteHandlerB : public BaseHandler
	{
	public:
		std::string Handle(std::string request)
		{
			if (request == "RequestB")
				return "Handler B, handlerered request " + request + "\n";
			else
				return BaseHandler::Handle(request);
		}
	};

	class ConcreteHandlerC : public BaseHandler
	{
	public:
		std::string Handle(std::string request)
		{
			if (request == "RequestC")
				return "Handler C, handlerered request " + request + "\n";
			else
				return BaseHandler::Handle(request);
		}
	};

	class ChainClient
	{
	public:
		void ClientCode(IHandler* chain)
		{
			std::vector<std::string> requests{ "RequestA", "RequestB", "RequestC", "RequestD" };

			for (auto request : requests)
			{
				std::cout << "Request: " << request << "\n";
				std::string result = chain->Handle(request);
				if (!result.empty())
					std::cout << result << "\n";
				else
					std::cout << " " << request << " not nandlerered\n";
			}
		}
	};

//////

	enum class PayType
	{
		Sberbank,
		TBank,
		WesternUnion
	};

	class PayRequest
	{
		std::map<PayType, bool> payChecks;
		int amount;
	
	public:
		PayRequest(int amount = 0) : amount{ amount }
		{
			payChecks[PayType::Sberbank] =
				payChecks[PayType::TBank] =
				payChecks[PayType::WesternUnion] = false;
		}

		void SetPayCheck(PayType type)
		{
			payChecks[type] = !payChecks[type];
		}

		bool IsPay(PayType type)
		{
			return payChecks[type];
		}

		int Amount() const { return amount; }
	};
}
