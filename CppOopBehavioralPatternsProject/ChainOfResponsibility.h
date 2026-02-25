#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

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

	class PaymentHandler
	{
	protected:
		PaymentHandler* successor{ nullptr };

	public:
		PaymentHandler*& Successor() { return this->successor; }

		void Push(PaymentHandler* successor)
		{
			if (this->successor)
				this->successor->Push(successor);
			else
				this->successor = successor;
		}

		void Insert(PaymentHandler* successor)
		{

		}

		void NextSuccessor(PayRequest* request)
		{
			if (this->successor)
				this->successor->PayHandler(request);
		}

		virtual void PayHandler(PayRequest* request) = 0;
	};

	class SberPaymentHandler : public PaymentHandler
	{
	public:
		void PayHandler(PayRequest* request)
		{
			if (request->IsPay(PayType::Sberbank))
			{
				// payment with Sber API
				std::cout << "Sber transfer is Ok. Amount = "
					<< std::to_string(request->Amount()) << "\n";
			}
			else
			{
				std::cout << "Sber transfer is None\n";
				PaymentHandler::NextSuccessor(request);
			}
		}
	};

	class TbankPaymentHandler : public PaymentHandler
	{
	public:
		void PayHandler(PayRequest* request)
		{
			if (request->IsPay(PayType::TBank))
			{
				// payment with TBank API
				std::cout << "TBank transfer is Ok. Amount = "
					<< std::to_string(request->Amount()) << "\n";
			}
			else
			{
				std::cout << "TBank transfer is None\n";
				PaymentHandler::NextSuccessor(request);
			}
		}
	};

	class WUPaymentHandler : public PaymentHandler
	{
	public:
		void PayHandler(PayRequest* request)
		{
			if (request->IsPay(PayType::WesternUnion))
			{
				// payment with WesternUnion API
				std::cout << "WU transfer is Ok. Amount = "
					<< std::to_string(request->Amount()) << "\n";
			}
			else
			{
				std::cout << "WU transfer is None\n";
				PaymentHandler::NextSuccessor(request);
			}
		}
	};


//////
	enum class Roles
	{
		All,
		Admin
	};

	class WebPage
	{
		std::string url;
		std::string content;

		Roles roles;
	public:
		WebPage(std::string url,
				std::string content,
				Roles roles = Roles::All)
			: url{ url },
			content{ content },
			roles{ roles }{ }

		std::string Url() const { return this->url; }
		std::string Content() const { return this->content; }
		Roles Roles() const { return this->roles; }
	};

	class WebServer
	{
		std::vector<WebPage*> pages;

	public:
		WebServer()
		{
			pages.push_back(new WebPage("/", "Home Page"));
			pages.push_back(new WebPage("/about", "About Company Page"));
			pages.push_back(new WebPage("/gallery", "Company's Work Gallery Page"));
			pages.push_back(new WebPage("/contacts", "Contacts Page"));

			pages.push_back(new WebPage("/admin", "Dashboard Main", Roles::Admin));
			pages.push_back(new WebPage("/admin/gallery", "Dashboard Gallery", Roles::Admin));
		}

		WebPage* GetPage(std::string url)
		{
			auto predicat = [url](auto page) {
					return page->Url() == url;
				};
			//auto it = std::find_if(pages.begin(), pages.end(), predicat);
			auto it = std::ranges::find_if(pages, predicat);
			return *it;
		}
	};

	class Database
	{
		std::map<std::string, std::string> admins;
	public:
		Database()
		{
			admins.insert("bobby", "qwerty");
			admins.insert("sammy", "12345");
			admins.insert("lenny", "lenny");
		}

		bool IsLogin(std::string login)
		{
			return admins.contains(login);
		}

		bool IsAdmin(std::string login, std::string password)
		{
			return admins[login] == password;
		}
	};

	class WebRequest
	{
		std::string url{};
		std::string login{};
		std::string password{};
	public:
		WebRequest(std::string url,
					std::string login = "",
					std::string password = "")
			: url{ url }, login{ login }, password{ password }{}

		std::string Url() const { return this->url; }
		std::string Login() const { return this->login; }
		std::string Password() const { return this->password; }
	};

	class FormHandler{};
	class IsPageFormHandler : public FormHandler{};
	class IsRoleFormHandler : public FormHandler {};
	class IsLoginFormHandler : public FormHandler {};
	class IsAdminFormHandler : public FormHandler {};
}
