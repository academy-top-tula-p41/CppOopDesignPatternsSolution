#pragma once

#include <iostream>
#include <vector>
#include <string>

class Element;
class Visitor
{
public:
	virtual void Visit(Element* element) = 0;
};

class Element
{
public:
	virtual void Accept(Visitor* visitor) = 0;
	virtual ~Element() = default;
};

class ConcreteElementA : public Element
{
public:
	void Accept(Visitor* visitor) override
	{
		visitor->Visit(this);
	}
	void BuisnessLogicElementA()
	{
		std::cout << "Buisness Logic Element A\n";
	}
};

class ConcreteElementB : public Element
{
public:
	void Accept(Visitor* visitor) override
	{
		visitor->Visit(this);
	}
	void BuisnessLogicElementB()
	{
		std::cout << "Buisness Logic Element B\n";
	}
};

class ConcreteVisiterA : public Visitor
{
public:
	void Visit(Element* element) override
	{
		ConcreteElementA* elementA = (ConcreteElementA*)element;

		std::cout << "Concrete Visiter A visit Element A\n";
		elementA->BuisnessLogicElementA();
	}
};

class ConcreteVisiterB : public Visitor
{
public:
	void Visit(Element* element) override
	{
		ConcreteElementB* elementB = (ConcreteElementB*)element;

		std::cout << "Concrete Visiter B visit Element B\n";
		elementB->BuisnessLogicElementB();
	}
};

class VisiterClient
{
public:
	void VisitToElement(Element* element, Visitor* visitor)
	{
		element->Accept(visitor);
	}
	void ClientCode()
	{
		VisitToElement(new ConcreteElementA(), new ConcreteVisiterA());
		VisitToElement(new ConcreteElementB(), new ConcreteVisiterB());
	}
};

//

class IClient;

class IClientVisitor
{
public:
	virtual void PersonVisit(IClient* client) = 0;
	virtual void CompanyVisit(IClient* client) = 0;
};

class IClient
{
protected:
	std::string name;
	std::string number;
	int amount;
public:
	virtual void Accept(IClientVisitor* visitor) = 0;

	IClient(std::string name, std::string number, int amount)
		: name{ name }, number{ number }, amount{ amount } {}

	std::string Name() { return name; }
	std::string Number() { return number; }
	int Amount() { return amount; }
};

class Person : public IClient
{
	std::string passport;
public:
	Person(std::string name, 
		std::string number, 
		std::string passport,
		int amount)
		: IClient(name, number, amount),
		passport{ passport }{ }

	std::string Passport() { return passport; }
	
	void Accept(IClientVisitor* visitor) override
	{
		visitor->PersonVisit(this);
	}
};

class Company : public IClient
{
	std::string license;
public:
	Company(std::string name,
		std::string number,
		std::string license,
		int amount)
		: IClient(name, number, amount),
		license{ license } {}

	std::string License() { return license; }

	void Accept(IClientVisitor* visitor) override
	{
		visitor->CompanyVisit(this);
	}
};

class Bank
{
	std::vector<IClient*> clients;
public:
	void Add(IClient* client)
	{
		clients.push_back(client);
	}

	void AcceptAll(IClientVisitor* visitor)
	{
		for (auto client : clients)
			client->Accept(visitor);
	}
};

class XmlVisitor : public IClientVisitor
{
public:
	void PersonVisit(IClient* client) override
	{
		Person* person = (Person*)client;
		std::string result = "<person>\n";
		result += "\t<name>" + person->Name() + "</name>\n";
		result += "\t<passport>" + person->Passport() + "</passport>\n";
		result += "\t<number>" + person->Number() + "</number>\n";
		result += "\t<amount>" + std::to_string(person->Amount()) + "</amount>\n";
		result += "</person>\n";

		std::cout << result << "\n";
	}

	void CompanyVisit(IClient* client) override
	{
		Company* company = (Company*)client;
		std::string result = "<company>\n";
		result += "\t<name>" + company->Name() + "</name>\n";
		result += "\t<license>" + company->License() + "</company>\n";
		result += "\t<number>" + company->Number() + "</number>\n";
		result += "\t<amount>" + std::to_string(company->Amount()) + "</amount>\n";
		result += "</company>\n";

		std::cout << result << "\n";
	}
};

class JsonVisitor : public IClientVisitor
{
public:
	void PersonVisit(IClient* client) override
	{
		Person* person = (Person*)client;
		std::string result = "person = {\n";
		result += "\t\"name>\": \"" + person->Name() + "\",\n";
		result += "\t\"passport>\": \"" + person->Passport() + "\",\n";
		result += "\t\"number>\": \"" + person->Number() + "\",\n";
		result += "\t\"amount>\": \"" + std::to_string(person->Amount()) + "\",\n";
		result += "}\n";

		std::cout << result << "\n";
	}

	void CompanyVisit(IClient* client) override
	{
		Company* company = (Company*)client;
		std::string result = "company = {\n";
		result += "\t\"name>\": \"" + company->Name() + "\",\n";
		result += "\t\"license>\": \"" + company->License() + "\",\n";
		result += "\t\"number>\": \"" + company->Number() + "\",\n";
		result += "\t\"amount>\": \"" + std::to_string(company->Amount()) + "\",\n";
		result += "}\n";

		std::cout << result << "\n";
	}
};

class BankWork
{
public:
	void Work()
	{
		Bank* bank = new Bank();
		bank->Add(new Person("Bobby", "ASD 1230987", "6785 901234", 1500000));
		bank->Add(new Company("TransMArket", "9087 df 54309", "LICENSE 7800 5623", 21000000));

		bank->AcceptAll(new XmlVisitor());
		std::cout << "\n";

		bank->AcceptAll(new JsonVisitor());
		std::cout << "\n";
	}
};