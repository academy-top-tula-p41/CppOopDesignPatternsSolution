#pragma once
#include <iostream>

class ServiceInterface
{
public:
	virtual std::string Operation() = 0;
};


class Service : public ServiceInterface
{
public:
	std::string Operation() override
	{
		return "Real Service Operation";
	}
};

class Proxy : public ServiceInterface
{
	Service* service;
	bool isConnect;

	bool CheckAccess() { return isConnect; }
public:
	Proxy(Service* service)
		: service{ service }, isConnect{ false } {}

	~Proxy() { delete service; }

	void LogIn() { isConnect = true; }
	void LogOut() { isConnect = false; }

	std::string Operation() override
	{
		if (CheckAccess())
			return service->Operation();
		else
			return "Proxy Service Operation";
	}
};

class ProxyClient
{
public:
	void ClientCode(ServiceInterface* service)
	{
		try
		{
			((Proxy*)service)->LogOut();
			std::cout << service->Operation();
		}
		catch (...)
		{
			std::cout << service->Operation();
		}
	}
};